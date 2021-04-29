/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/renderer.h"
#include "internal/gui/widgets/label.h"
#include "internal/gui/widgetfactory.h"
#include "internal/os/lock_guard.h"
#include "extern/imgui/imgui.h"
#include "extern/imgui/imgui_internal.h"

extern "C" {
#include "extern/rebsdev/src/glue/face/face.h"
}

extern "C" FaceFont gDefaultFont;

namespace GUI {

Renderer::Renderer(Os::Mutex& rFrameSynchronizerP)
    : rFrameSynchronizerM{rFrameSynchronizerP}
    , newFontAddedM{false}
    , fontsM{&rFrameSynchronizerM}
{

}

void Renderer::addMainWindow(IWindow* pMainWindowP)
{
    commandsM.set(
        Widget::WidgetCommand::Create, 
        PARENT_NONE, 
        pMainWindowP);    
}

Id Renderer::createWidget(const char* pFaceDescriptionP)
{
    return widgetStub(pFaceDescriptionP, [=](GlueFace const& rFaceP, FaceCounters const& rCountersP)->Id{
        return createWidget(rFaceP, rCountersP);
    });
}

void Renderer::updateWidget(const char* pFaceDescriptionP)
{

}

void Renderer::removeWidget(const char* pFaceDescriptionP)
{

}

void Renderer::render()
{
    // check for new commands
    Widget::CommandElem command = commandsM.get();
    if (command.getType() != Widget::WidgetCommand::None)
    {
        Widget::Storage::Index itElem;
        switch(command.getType())
        {
        case Widget::WidgetCommand::Create:
            if (command.getGuiType() == Widget::GuiElemType::Widget)
                itElem = widgetsM.add(command.getWidget(), command.getParentId());
            else
                itElem = widgetsM.add(command.getWindow(), command.getParentId());            
            if (command.getParentId() == PARENT_NONE)
            {
                rootWidgetsM.push_back(itElem);
            }
            break;
        case Widget::WidgetCommand::Update:
            {
                Os::lock_guard guard{syncWidgetsM};
            }
            break;
        case Widget::WidgetCommand::Remove:
            {
                Os::lock_guard guard{syncWidgetsM};
            }
            break;
        }
        // TODO: execute command
        // ...
    }
    // Render elements
    for (auto itElem : rootWidgetsM)
    {
        renderino(*itElem);
    }
}

void Renderer::setNewFontAdded(bool valueP)
{
    newFontAddedM = valueP;
}

bool Renderer::getNewFontAdded() const
{
    return newFontAddedM;
}

void Renderer::renderino(Widget::StorageElem const& rElemP)
{
    rElemP.widget.pWidget->beginRender();
    Widget::Storage::Index itEnd{rElemP.childLast};
    if (itEnd != widgetsM.getElements().end())
    {
        ++itEnd;
    }
    for (Widget::Storage::Index it = rElemP.childFirst; it != itEnd; ++it)
    {
        renderino(*it);
    }
    rElemP.widget.pWidget->endRender();
}

bool Renderer::parseFaceDescription(const char* faceDescriptionP, GlueFace& rFaceP, FaceCounters& rCountersP)
{
    if (void* pBlock; pBlock = parse_block(faceDescriptionP))
    {
        return (get_face_by_index(pBlock, &rFaceP, &rCountersP) == 0);
    }
    return false;
}

Id Renderer::createWidget(GlueFace const& rFaceP, FaceCounters const& rCountersP)
{
    if (!rFaceP.type.none)
    {
        switch(rFaceP.type.value)
        {
        case TYPE_LABEL:
            return createLabel(rFaceP);
        }
    }
    // TODO: draw effect by extracting effect elements using rCountersP.effectCount
    // ...
    return INVALID_WIDGET_ID;    
}

Id Renderer::widgetStub(char const* pFaceDescriptionP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP)
{
    FaceCounters counters; 
    if (GlueFace face; parseFaceDescription(pFaceDescriptionP, face, counters))
    {
        return widgetStub(face, widgetCreatorP, counters);
    }
    return INVALID_WIDGET_ID;
}

Id Renderer::widgetStub(GlueFace const& rFaceP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP, FaceCounters& rCountersP)
{
    // render widget
    Id result = widgetCreatorP(rFaceP, rCountersP);
    // render widget children if it has
    for (int i = 0; i < rCountersP.paneCount; i++)
    {
        GlueFace* pChild{nullptr};
        GlueFace childFaces;
        if (!rFaceP.pane.none && (get_face_pane_elem((void*)rFaceP.pane.value, i, (void**)&pChild) == SUCCESS) && !pChild->pane.none)
        {
            FaceCounters counters;
            counters.paneCount = get_face_pane_count_by_index((void*)pChild->pane.value, FIELD_PANE, &childFaces);
            void* pChildRaw{nullptr};
            if (get_block_elem(rFaceP.pane.value, i, &pChildRaw) == SUCCESS)
            {
                counters.effectCount = get_face_effect_count_by_index(pChildRaw, FIELD_EFFECT, &childFaces);
                widgetStub(*pChild, widgetCreatorP, counters);
            }
        }
    }
    return result;
}

template <typename T>
Id Renderer::createStub(
    GlueFace const& rFaceP, 
    std::function<T*(GlueFace const&)> createP, 
    std::function<void(void)> beforeUpdateP)
{
    Id idWidget{INVALID_WIDGET_ID};
    if (T* pT = createP(rFaceP); pT)
    {
        idWidget = pT->getId();
        if (beforeUpdateP)
        {
            beforeUpdateP();
        }
        pT->update(rFaceP);
        commandsM.set(
            Widget::WidgetCommand::Create, 
            (rFaceP.parent.none) ? PARENT_NONE : rFaceP.parent.value, 
            pT);
    }
    return idWidget;
}

Font* Renderer::createFont(FaceFont const& rFontP)
{
    Font* pFont{nullptr};
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    Bind::Rebol2::FontInfo fontInfo;
    Bind::Rebol2::Text fontName = (rFontP.path.none) ? gDefaultFont.path.value : rFontP.path.value;
    if (auto found = fontsM.get(fontName, fontInfo); !found || (found && (fontInfo.faceFontM != rFontP)))
    {
        static ImFontConfig fntConfig;
        rFrameSynchronizerM.lock();
        pFont = pImGuiContext->IO.Fonts->AddFontFromFileTTF(
            fontName.c_str()
            , rFontP.size.none ? gDefaultFont.size.value : rFontP.size.value
            , &fntConfig
        );
        fontInfo.faceFontM = rFontP;
        fontInfo.pFontM = pFont;
        fontsM.add(fontName, fontInfo);
        newFontAddedM = true;
        rFrameSynchronizerM.unlock();
    }
    else
    {
        pFont = fontInfo.pFontM;
    }
    
    return pFont;
}

Id Renderer::createLabel(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            return WidgetFactory::instance().createLabel(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
            );
        }
    );
}

} // namespace GUI