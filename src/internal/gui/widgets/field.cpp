/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/field.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Field::Field(const char* textP, ImFont* pFontP, int styleP)
    : Area(textP, pFontP, styleP)
{
    // TODO: replacement must be done on rebol side
    replace(textBufferM, "^/", "\n");
}

Field::Field(const char* textP, ImFont* pFontP, int styleP, const char* pHintP)
    : Field(textP, pFontP, styleP)
{
    pHintM = pHintP;
}

void Field::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textBufferM = rFaceP.text.value;
    }
}

bool Field::InputText()
{
    // store extra attributes
    WidgetAttribs attrib;
    attrib.externId = idM;
    attrib.parentExternId = ImGui::GetCurrentWindow()->ExternID;
    ImGui::SetNextItemWidth((float)widthM);
    SaveCurrentStyle();
    SetStyleBgColor(ImGuiCol_FrameBg);
    bool bres{false};
    if (pHintM)
    {
        bres = ImGui::InputTextWithHint("", pHintM, (char*)textBufferM.c_str(), textBufferM.capacity() + 1, styleM, InputTextCallback, this, &attrib);
    }
    else
    {
        bres = ImGui::InputText("", (char*)textBufferM.c_str(), textBufferM.capacity() + 1, styleM, InputTextCallback, this, &attrib);
    }
    RestoreStyle();
    return bres;
}


} // namespace Widget
} // namespace Gui