/**
 * Author: 		Iosif Haidu
 * Description: Radio button widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/basewidget.h"
#include "internal/tools/safemap.h"
#include <string>

namespace GUI {
namespace Widget {

class RadioButton : public Base<IWidget>
{
private:
    class Group
    {
    public:
        void setSelection(int groupIdP, int valueP);
        int getSelection(int groupIdP) const;
    private:
        using GroupSelectionCollection = Tools::SafeMap<int, int>;  // group id/selection value
        GroupSelectionCollection groupSelectionCollectionM;
    };

public:
    /**
     * Checkbox 
     * 
     * @param  {char*} textP        : text of checkbox
     * @param  {ImFont*} pFontP     : font for text§
     * @param  {Color*} pMarkColorP : color for check mark
     */
    RadioButton(const char* textP, ImFont* pFontP, Color* pMarkColorP, int groupIdP, int selectedP);

    /** see IWidget::clone() */
    IWidget* clone() override;
    RadioButton& operator=(const RadioButton& rOpP);

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;
    /** see IWidget::update() */
    void update(GlueFace const& rFaceP, bool partOfCreationP = false) override;

private:
    std::string textM;
    static Group groupsM;
    static int optionValueCrtIndexM;
    int groupIdM;
    int optionValueM;
    Color checkMarkColorM;
};

} // namespace Widget
} // namespace Gui