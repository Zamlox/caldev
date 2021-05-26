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

bool Field::InputText()
{
    // store extra attributes
    WidgetAttribs attrib;
    attrib.externId = idM;
    attrib.parentExternId = ImGui::GetCurrentWindow()->ExternID;
    return ImGui::InputText("", (char*)textBufferM.c_str(), textBufferM.capacity() + 1, styleM, InputTextCallback, this, &attrib);
}


} // namespace Widget
} // namespace Gui