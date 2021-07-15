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

        SaveCurrentStyle();

        SetStyleColor(ImGuiCol_FrameBg, bgColorM);

        Color hoveredColor = GetStyleColor(ImGuiCol_FrameBgHovered);
        hoveredColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_FrameBgHovered, hoveredColor);

        Color activeColor = GetStyleColor(ImGuiCol_FrameBgActive);
        activeColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_FrameBgActive, activeColor);

        Color buttonHoveredColor = GetStyleColor(ImGuiCol_ButtonHovered);
        buttonHoveredColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_ButtonHovered, buttonHoveredColor);

        Color buttonColor = GetStyleColor(ImGuiCol_Button);
        buttonColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_Button, buttonColor);

        //Color textColor = GetStyleColor(ImGuiCol_Text);
        //textColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_Text, frColorM);                     // Currently this sets also arrow color. Check ImGui::BeginCombo()

        Color borderColor = GetStyleColor(ImGuiCol_Border);
        borderColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_Border, borderColor);                     

        Color headerColor = GetStyleColor(ImGuiCol_Header);
        headerColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_Header, headerColor);                     

        Color headerHoveredColor = GetStyleColor(ImGuiCol_HeaderHovered);
        headerHoveredColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_HeaderHovered, headerHoveredColor);                     

        Color headerActiveColor = GetStyleColor(ImGuiCol_HeaderActive);
        headerActiveColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_HeaderActive, headerActiveColor);                     

        // a popup will be opened
        unsigned int bgColor = ::ImGui::ColorConvertFloat4ToU32(bgColorM);
        ::ImGui::SetNextWindowBgColor(bgColor);
        ::ImGui::SetNextWindowBgAlpha(bgColorM.w);

        ImGui::SetNextItemWidth(widthM);
        ImGui::Combo("", &selectedM, pItemsM, countM);

        RestoreStyle();
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