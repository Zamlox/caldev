/**
 * Author: 		Iosif Haidu
 * Description: Image widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "api/imp/apiconst.h"
#include "internal/gui/iwidget.h"
#include "internal/gui/basewidget.h"
#include <string>

namespace GUI {
namespace Widget {

class Image : public Base<IWidget>
{
public:
    Image(Api::GuiType guiTypeP, const char* pFileNameP, int desiredChannelsP);
    Image(Api::GuiType guiTypeP, unsigned char* pDataP, int widthP, int heightP, int nChannelsP);
    ~Image();

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    void renderForOpenGl2();

    Api::GuiType guiTypeM;
    unsigned char* pDataM;
    int nChannelsM;
    unsigned int textureIdM;
    int imgWidthM;
    int imgHeightM;
};

} // namespace Widget
} // namespace Gui