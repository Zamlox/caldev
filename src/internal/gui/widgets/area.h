/**
 * Author: 		Iosif Haidu
 * Description: Area widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/basewidget.h"
#include <string>


namespace GUI {
namespace Widget {
    
class Area : public Base<IWidget>
{
public:
    Area(const char* textP, ImFont* pFontP, int styleP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;

    friend int InputTextCallback(ImGuiInputTextCallbackData* data);

private:
    std::string textBufferM;
    int styleM;

};

} // namespace Widget
} // namespace Gui