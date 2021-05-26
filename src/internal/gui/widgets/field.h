/**
 * Author: 		Iosif Haidu
 * Description: Area widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/widgets/area.h"
#include <string>


namespace GUI {
namespace Widget {

class Field : public Area
{
public:
    Field(const char* textP, ImFont* pFontP, int styleP);

    friend int InputTextCallback(ImGuiInputTextCallbackData* data);

protected:
    bool InputText() override;
};

} // namespace Widget
} // namespace Gui