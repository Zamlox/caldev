/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/renderer.h"
#include "internal/gui/widgets/label.h"
#include "internal/gui/widgetfactory.h"
#include "internal/os/util.h"
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
    , stashedM{true}
    , isInitialUnstashM{false}
{

}

void Renderer::addMainWindow(IWindow* pMainWindowP)
{
    commandsM.set(
        Widget::WidgetCommand::Create, 
        PARENT_NONE, 
        pMainWindowP);    
}

Id Renderer::createWidget(const char* pFaceDescriptionP, Api::GuiType guiTypeP)
{
    guiTypeM = guiTypeP;
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
        case Widget::WidgetCommand::Stash:
            stashedM = true;
            glfwSwapInterval(0);
            break;
        case Widget::WidgetCommand::Unstash:
            if (!isInitialUnstashM)
            {
                isInitialUnstashM = true;
            }
            else
                stashedM = false;
            glfwSwapInterval(1);
            break;
        }
        // TODO: execute command
        // ...
    }
    // Render elements if not stashed
    if (isInitialUnstashM)
    {
        for (auto itElem : rootWidgetsM)
        {
            renderino(*itElem);
        }
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

void Renderer::stash()
{
    commandsM.set(
        Widget::WidgetCommand::Stash, 
        INVALID_WIDGET_ID, 
        (IWidget*)nullptr);
}

void Renderer::unstash()
{
    commandsM.set(
        Widget::WidgetCommand::Unstash, 
        INVALID_WIDGET_ID, 
        (IWidget*)nullptr);
}

bool Renderer::isInitialUnstash() const
{
    return isInitialUnstashM;
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

bool Renderer::getOptionValue(int optionTypeP, ElemsManager* pElemsP, OptionsValue& rOptionValueP)
{
    for (int i = 0; i < pElemsP->count; i++)
    {
        if (pElemsP->block.pOptions[i].type == optionTypeP)
        {
            rOptionValueP = pElemsP->block.pOptions[i].value;
            return true;
        }
    }
    return false;
}

Id Renderer::createWidget(GlueFace const& rFaceP, FaceCounters const& rCountersP)
{
    if (!rFaceP.type.none)
    {
        switch(rFaceP.type.value)
        {
        case TYPE_WINDOW:
            return createWindow(rFaceP);
        case TYPE_LABEL:
            return createLabel(rFaceP);
        case TYPE_AREA:
            return createArea(rFaceP);
        case TYPE_FIELD:
            return createField(rFaceP);
        case TYPE_BUTTON:
            return createButton(rFaceP);
        case TYPE_CHECKBOX:
            return createCheckbox(rFaceP);
        case TYPE_RADIOBUTTON:
            return createRadioButton(rFaceP);
        case TYPE_IMAGE:
            return createImage(rFaceP);
        case TYPE_COMBOBUTTON:
            return createCombo(rFaceP);
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
        pT->update(rFaceP, true);
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
    if (auto found = fontsM.get(fontName, fontInfo); !found)
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

Id Renderer::createWindow(GlueFace const& rFaceP)
{
    return createStub<IWindow>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            return WidgetFactory::instance().createWindow(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , WindowFlags_SubWindow      // TODO: find a way to specify flags within face decription
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
                , rFaceP.parent.none ? PARENT_NONE : rFaceP.parent.value
            );
        }
    );
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

Id Renderer::createArea(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            return WidgetFactory::instance().createArea(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
                , (rFaceP.options.value->count) ? rFaceP.options.value->block.pOptions[0].value.iValue : AREA_NONE
            );
        }
    );
   return 0;
}

Id Renderer::createField(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            int areaFlags{AREA_NONE};
            const char* hint{nullptr};
            if (rFaceP.options.none == 0)
            {
                for (int i = 0; i < rFaceP.options.value->count; i++)
                {
                    if (rFaceP.options.value->block.pOptions[i].type == OPTIONS_TYPE_AREA)
                        areaFlags = rFaceP.options.value->block.pOptions[i].value.iValue;
                    else if (rFaceP.options.value->block.pOptions[i].type == OPTIONS_TYPE_FIELD_HINT)
                    {
                        hint = rFaceP.options.value->block.pOptions[i].value.sValue;
                    }
                }
            }
            return WidgetFactory::instance().createField(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
                , areaFlags
                , hint
            );
        }
    );
}

Id Renderer::createButton(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            return WidgetFactory::instance().createButton(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
            );
        }
    );
}

Id Renderer::createCheckbox(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            OptionsValue optCheckMarkColor;
            bool isCheckMark = NOT_NONE(rFaceP.options) && getOptionValue(OPTIONS_TYPE_CHECKBOX_MARK, rFaceP.options.value, optCheckMarkColor);
            return WidgetFactory::instance().createCheckbox(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
                , isCheckMark ? &optCheckMarkColor.colorValue : (::Color*)nullptr
            );
        }
    );
}

Id  Renderer::createRadioButton(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            OptionsValue optCheckMarkColor;
            OptionsValue optRadioGroupId;
            OptionsValue optRadioSelected;
            bool isCheckMark{false};
            bool isGroupId{false};
            if (NOT_NONE(rFaceP.options))
            {
                isCheckMark = getOptionValue(OPTIONS_TYPE_CHECKBOX_MARK, rFaceP.options.value, optCheckMarkColor);
                isGroupId = getOptionValue(OPTIONS_TYPE_RADIO_GROUP, rFaceP.options.value, optRadioGroupId);
                optRadioSelected.iValue = 0;
                getOptionValue(OPTIONS_TYPE_RADIO_SELECTED, rFaceP.options.value, optRadioSelected);
            }
            return WidgetFactory::instance().createRadioButton(
                (rFaceP.text.none) ? "" : rFaceP.text.value
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
                , isCheckMark ? &optCheckMarkColor.colorValue : (::Color*)nullptr
                , isGroupId ? optRadioGroupId.iValue : 1
                , optRadioSelected.iValue
            );
        }
    );
}

Id  Renderer::createImage(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            return WidgetFactory::instance().createImage(
                guiTypeM
                , rFaceP.image.value.data
                , rFaceP.image.value.width
                , rFaceP.image.value.height
                , rFaceP.image.value.channels
            );
        }
    );
}

Id  Renderer::createCombo(GlueFace const& rFaceP)
{
    return createStub<IWidget>(
        rFaceP,
        [=](GlueFace const& rFaceP){
            int selectIndex{-1};
            const char* selectValue{nullptr};
            if (!rFaceP.options.none)
            {
                for (int i = 0; i < rFaceP.options.value->count; i++)
                {
                    if (rFaceP.options.value->block.pOptions[i].type == OPTIONS_TYPE_COMBO_SEL_INDEX)
                    {
                        selectIndex = rFaceP.options.value->block.pOptions[i].value.iValue;
                    }
                    else if (rFaceP.options.value->block.pOptions[i].type == OPTIONS_TYPE_COMBO_SEL_VALUE)
                    {
                        selectValue = rFaceP.options.value->block.pOptions[i].value.sValue;
                        if (!rFaceP.data.none)
                        {
                            for (int j = 0; j < rFaceP.data.value.value.textItems.size; j++)
                            {
                                if (!strcmp(selectValue, rFaceP.data.value.value.textItems.elems[j]))
                                {
                                    selectIndex = j;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            return WidgetFactory::instance().createComboButton(
                rFaceP.data.value.value.textItems.elems
                , rFaceP.data.value.value.textItems.size
                , selectIndex
                , createFont((rFaceP.font.none) ? gDefaultFont : rFaceP.font.value)
            );
        }
    );
}

} // namespace GUI