/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/button.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Button::Button(const char* textP, ImFont* pFontP)
    : Base{pFontP}
    , textM{textP}
{
    // TODO: replacement must be done on rebol side
    replace(textM, "^/", "\n");
}

void Button::beginRender()
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
        SetStyleFramePadding(ImVec2(0.0f, 0.0f));
        SetStyleBgColor(ImGuiCol_Button);
        ImGui::Button(textM.c_str(), ImVec2(widthM, heightM), &attrib);
        RestoreStyle();
    }
}

void Button::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Button::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textM = rFaceP.text.value;
    }
}

} // namespace Widget
} // namespace Gui