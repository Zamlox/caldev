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

    /** see IWidget::clone() */
    IWidget* clone() override;
    Label& operator=(const Label& rOpP);

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