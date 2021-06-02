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

int InputTextCallback(ImGuiInputTextCallbackData* data);
    
class Area : public Base<IWidget>
{
public:
    Area(const char* textP, ImFont* pFontP, int styleP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP) override;

    friend int InputTextCallback(ImGuiInputTextCallbackData* data);

protected:
    virtual bool InputText();

    std::string textBufferM;
    int styleM;

};

} // namespace Widget
} // namespace Gui