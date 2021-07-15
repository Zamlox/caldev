/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/checkbox.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Checkbox::Checkbox(const char* textP, ImFont* pFontP, Color* pMarkColorP)
    : Base{pFontP}
    , textM{textP}
    , pressedM{true}
    , checkStatusM{false}
    , checkMarkColorM{pMarkColorP ? *pMarkColorP : GetStyleColor(ImGuiCol_CheckMark)}
{
    // TODO: replacement must be done on rebol side
    replace(textM, "^/", "\n");
}

IWidget* Checkbox::clone()
{
    IWidget* pWidget = WidgetFactory::instance().createCheckbox("", nullptr, nullptr, true);
    Checkbox* pCheckbox = static_cast<Checkbox*>(pWidget);
    *pCheckbox = *this;
    return pCheckbox;
}

Checkbox& Checkbox::operator=(const Checkbox& rOpP)
{
    if (&rOpP != this)
    {
        Base<IWidget>::operator=(rOpP);
        textM           = rOpP.textM;
        pressedM        = rOpP.pressedM;
        checkStatusM    = rOpP.checkStatusM;
        checkMarkColorM = rOpP.checkMarkColorM;
    }
    return *this;
}

void Checkbox::beginRender()
{
    ImGuiID id;
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        // store extra attributes
        WidgetAttribs attrib(
            ImGui::ColorConvertFloat4ToU32(bgColorM)
            , ImGui::ColorConvertFloat4ToU32(frColorM)
            , alignM
            , ImRect(xM, yM, xM + widthM, yM + heightM)
            , (isWrapM) ? widthM : 0.0
            , ImRect{0, 0, 0, 0}
        );
        
        if (pFontM) ImGui::PushFont(pFontM);
        SaveCurrentStyle();
        Color hoveredColor = GetStyleColor(ImGuiCol_FrameBgHovered);
        hoveredColor.w = bgColorM.w;
        Color activeColor = GetStyleColor(ImGuiCol_FrameBgActive);
        activeColor.w = bgColorM.w;
        SetStyleColor(ImGuiCol_FrameBg, bgColorM);
        SetStyleColor(ImGuiCol_FrameBgHovered, hoveredColor);
        SetStyleColor(ImGuiCol_FrameBgActive, activeColor);
        SetStyleColor(ImGuiCol_CheckMark, checkMarkColorM);
        SetStyleFgColor(ImGuiCol_Text);
        pressedM = ImGui::Checkbox(textM.c_str(), &checkStatusM, nullptr);
        RestoreStyle();
    }
}

void Checkbox::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Checkbox::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textM = rFaceP.text.value;
    }
}

} // namespace Widget
} // namespace Gui