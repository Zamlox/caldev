/**
 * Author: 		Iosif Haidu
 * Description: Combo button widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/basewidget.h"
#include <string>
#include <vector>

namespace GUI {
namespace Widget {

class Combo : public Base<IWidget>
{
public:
    /**
     * Combo 
     * 
     * @param  {char*} pItemsP      : list of text items
     * @param  {int} countP         : count of text items
     * @param  {int} selectedP      : selected item
     * @param  {ImFont*} pFontP     : font for text
     */
    Combo(const char** pItemsP, int countP, int selectedP, ImFont* pFontP);
    ~Combo();

    /** see IWidget::clone() */
    IWidget* clone() override;
    Combo& operator=(const Combo& rOpP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    const char** pItemsM;
    int countM;
    int selectedM;
    /** Flag used to avoid destroying pItemsM twice if instance was cloned */
    bool sharedM;
};

} // namespace Widget
} // namespace Gui