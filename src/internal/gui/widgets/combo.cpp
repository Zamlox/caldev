/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/combo.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Combo::Combo(const char** pItemsP, int countP, int selectedP, ImFont* pFontP)
    : Base{pFontP}
    , pItemsM{pItemsP}
    , countM{countP}
    , selectedM{selectedP}
    , sharedM{false}
{
}

Combo::~Combo()
{
    if (!sharedM)
        destroyData(&pItemsM);
}

IWidget* Combo::clone()
{
    IWidget* pWidget = WidgetFactory::instance().createComboButton(nullptr, 0, 0, nullptr, true);
    Combo* pCombo = static_cast<Combo*>(pWidget);
    *pCombo = *this;
    return pCombo;
}

Combo& Combo::operator=(const Combo& rOpP)
{
    if (&rOpP != this)
    {
        Base<IWidget>::operator=(rOpP);
        countM      = rOpP.countM;
        selectedM   = rOpP.selectedM;
        pItemsM     = rOpP.pItemsM;
        sharedM     = true;
    }
    return *this;
}

void Combo::beginRender()
{
    ImGuiID id;
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        
        if (pFontM) ImGui::PushFont(pFontM);
        ImGui::SetNextItemWidth(widthM);
        ImGui::Combo("", &selectedM, pItemsM, countM);
    }
}

void Combo::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Combo::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!partOfCreationP)
    {
        destroyData(&pItemsM);
        if (!rFaceP.data.none)
        {
            pItemsM = rFaceP.data.value.value.textItems.elems;
            countM  = rFaceP.data.value.value.textItems.size;
        }
    }
}

} // namespace Widget
} // namespace Gui