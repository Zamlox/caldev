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

class Checkbox : public Base<IWidget>
{
public:
    /**
     * Checkbox 
     * 
     * @param  {char*} textP        : text of checkbox
     * @param  {ImFont*} pFontP     : font for text§
     * @param  {Color*} pMarkColorP : color for check mark
     */
    Checkbox(const char* textP, ImFont* pFontP, Color* pMarkColorP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    std::string textM;
    bool pressedM;
    bool checkStatusM;
    Color checkMarkColorM;
};

} // namespace Widget
} // namespace Gui