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

class Button : public Base<IWidget>
{
public:
    /**
     * Button 
     * 
     * @param  {char*} textP    : text of button
     * @param  {ImFont*} pFontP : font for text
     */
    Button(const char* textP, ImFont* pFontP);

    /** see IWidget::clone() */
    IWidget* clone() override;
    Button& operator=(const Button& rOpP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    std::string textM;
};

} // namespace Widget
} // namespace Gui