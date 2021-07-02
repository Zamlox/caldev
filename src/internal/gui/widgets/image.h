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

    /** see IWidget::clone() */
    IWidget* clone() override;
    Image& operator=(const Image& rOpP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    void renderForOpenGl2(bool forceP = false);

    Api::GuiType guiTypeM;
    unsigned char* pDataM;
    int nChannelsM;
    int desiredChannelsM;
    unsigned int textureIdM;
    int imgWidthM;
    int imgHeightM;
    bool canBeDeletedM;
};

} // namespace Widget
} // namespace Gui