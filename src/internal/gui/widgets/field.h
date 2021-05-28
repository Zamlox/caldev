/**
 * Author: 		Iosif Haidu
 * Description: Area widget
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/widgets/area.h"
#include <string>


namespace GUI {
namespace Widget {

class Field : public Area
{
public:
    
    /**
     * Construcor for field. 
     * 
     * @param  {char*} textP    : initial text
     * @param  {ImFont*} pFontP : font
     * @param  {int} styleP     : style
     */
    Field(const char* textP, ImFont* pFontP, int styleP);
    /**
     * Constructor for foeld with hint text. 
     * 
     * @param  {char*} textP    : initial text
     * @param  {ImFont*} pFontP : font
     * @param  {int} styleP     : style
     * @param  {char*} pHintP   : hint text
     */
    Field(const char* textP, ImFont* pFontP, int styleP, const char* pHintP);

    /** see IWidget::update() */
    void update(GlueFace const& rFaceP) override;

    friend int InputTextCallback(ImGuiInputTextCallbackData* data);

protected:
    bool InputText() override;
    const char* pHintM;
};

} // namespace Widget
} // namespace Gui