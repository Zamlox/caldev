/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/checkbox.h"
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
        SetStyleColor(ImGuiCol_CheckMark, checkMarkColorM);
        SetStyleFgColor(ImGuiCol_Text);
        pressedM = ImGui::Checkbox(textM.c_str(), &checkStatusM, &attrib);
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

void Checkbox::update(GlueFace const& rFaceP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textM = rFaceP.text.value;
    }
}

} // namespace Widget
} // namespace Gui