/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/area.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    Area* pArea = (Area*)data->UserData;
    if (pArea->styleM | AREA_CALLBACK_RESIZE && data->EventFlag == AREA_CALLBACK_RESIZE)
    {
        std::string& str = pArea->textBufferM;
        IM_ASSERT(data->Buf == str.c_str());
        str.resize(data->BufTextLen);
        data->Buf = (char*)str.c_str();
    }
    else if (pArea->styleM | AREA_CALLBACK_COMPLETION && data->EventFlag == AREA_CALLBACK_COMPLETION)
    {
        // TODO: send event for completion
        // ...
    }
    else if (pArea->styleM | AREA_CALLBACK_HISTORY && data->EventFlag == AREA_CALLBACK_HISTORY)
    {
        // TODO: send event for history
        // ...
    }
    else if (pArea->styleM | AREA_CALLBACK_ALWAYS && data->EventFlag == AREA_CALLBACK_ALWAYS)
    {
        // TODO: send event for always
        // ...
    }
    else if (pArea->styleM | AREA_CALLBACK_CHAR_FILTER && data->EventFlag == AREA_CALLBACK_CHAR_FILTER)
    {
        // TODO: send event for char filter
        // ...
    }
    else if (pArea->styleM | AREA_CALLBACK_EDIT && data->EventFlag == AREA_CALLBACK_EDIT)
    {
        // TODO: send event for edit
        // ...
    }
    return 0;
}

Area::Area(const char* textP, ImFont* pFontP, int styleP)
    : Base{pFontP}
    , textBufferM{textP}
    , styleM{styleP | AREA_CALLBACK_RESIZE}
{
    // TODO: replacement must be done on rebol side
    replace(textBufferM, "^/", "\n");
}

void Area::beginRender()
{
    ImGuiID id;
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        
        if (pFontM) ImGui::PushFont(pFontM);
        SaveCurrentStyle();
        SetStyleFgColor(ImGuiCol_Text);
        InputText();
        RestoreStyle();
    }
}

void Area::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Area::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textBufferM = rFaceP.text.value;
    }
}

bool Area::InputText()
{
    ImGui::SetNextWindowBgColor(ImGui::ColorConvertFloat4ToU32(bgColorRGBM));
    if (alphaM != 0.0)
        ImGui::SetNextWindowBgAlpha(alphaM);
    // store extra attributes
    WidgetAttribs attrib;
    attrib.externId = idM;
    attrib.parentExternId = ImGui::GetCurrentWindow()->ExternID;
    return ImGui::InputTextMultiline("", (char*)textBufferM.c_str(), textBufferM.capacity() + 1, ImVec2(widthM, heightM), styleM, InputTextCallback, this, &attrib);
}

} // namespace Widget
} // namespace Gui