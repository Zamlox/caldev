/**
 * Author: 		Iosif Haidu
 * Description: Label widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/basewidget.h"
#include <string>

namespace GUI {
namespace Widget {

class Label : public Base<IWidget>
{
public:
    Label(const char* textP, ImFont* pFontP);

    void render() override;

private:
    std::string textM;
};

} // namespace Widget
} // namespace Gui