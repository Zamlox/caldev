/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/radio.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

namespace {

constexpr int INVALID_SELECTION{-1};

} // anonymous namespace

RadioButton::Group RadioButton::groupsM;
int RadioButton::optionValueCrtIndexM{0};

void RadioButton::Group::setSelection(int groupIdP, int valueP)
{
    groupSelectionCollectionM.set(groupIdP, valueP);
}

int RadioButton::Group::getSelection(int groupIdP) const
{
    int selection{INVALID_SELECTION};
    return groupSelectionCollectionM.get(groupIdP, selection) ? selection : INVALID_SELECTION;
}

RadioButton::RadioButton(const char* textP, ImFont* pFontP, Color* pMarkColorP, int groupIdP, int selectedP)
    : Base{pFontP}
    , textM{textP}
    , groupIdM{groupIdP}
    , checkMarkColorM{pMarkColorP ? *pMarkColorP : GetStyleColor(ImGuiCol_CheckMark)}
{
    // TODO: replacement must be done on rebol side
    replace(textM, "^/", "\n");
    optionValueCrtIndexM++;
    optionValueM = optionValueCrtIndexM;
    if (selectedP)
    {
        groupsM.setSelection(groupIdM, optionValueM);
    }
}

void RadioButton::beginRender()
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
        if (ImGui::RadioButton(textM.c_str(), groupsM.getSelection(groupIdM) == optionValueM, nullptr))
        { 
            groupsM.setSelection(groupIdM, optionValueM);
        }
        RestoreStyle();
    }
}

void RadioButton::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void RadioButton::update(GlueFace const& rFaceP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textM = rFaceP.text.value;
    }
}

} // namespace Widget
} // namespace Gui