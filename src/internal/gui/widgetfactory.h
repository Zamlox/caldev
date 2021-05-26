/**
 * Author: 		Iosif Haidu
 * Description: Implementation of IWidgetFactory
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwindow.h"
#include "internal/gui/iwidget.h"
#include "extern/GSL/include/gsl/string_span.h"

namespace GUI
{

/**
 * Factory for widgets
 */
class WidgetFactory
{
public:
    /**
     * Get unique instance.
     * @return {WidgetFactory}  : instance of WidgetFactory
     */
    static WidgetFactory& instance();
    
    /**
     * Create window.
     * 
     * @param  {czstring<>} titleP : title of window
     * @param  {int} flags         : flags for window creation
     * @param  {Font*} pFontP      : font for window
     * @return {owner<IWindow>*}   : instance of created window
     */
    owner<IWindow*> createWindow(czstring<> titleP, int flags, Font* pFontP, Id parentIdP = PARENT_NONE);
    /**
     * Destroy window.
     * 
     * @param  {owner<IWindow*} > : instance of window to be destroyed
     */
    void destroyWindow(owner<IWindow*>& pWindowP);
    /** Destroy widget */
    void destroyWidget(owner<IWidget*>& pWidgetP);

    /**
     * Create label widget.
     * 
     * @param  {char*} textP    : text to display
     * @param  {ImFont*} pFontP : font of text
     * @return {IWidget*}       : widget instance
     */
    IWidget* createLabel(const char* textP, ImFont* pFontP);
    /**
     * Create area widget.
     * 
     * @param  {char*} textP    : text to display
     * @param  {ImFont*} pFontP : font of text
     * @param  {int} styleP     : style of widget
     * @return {IWidget*}       : widget instance
     */
    IWidget* createArea(const char* textP, ImFont* pFontP, int styleP);
    
    /**
     * Create field widget.
     * 
     * @param  {char*} textP    : text to display
     * @param  {ImFont*} pFontP : font of text
     * @param  {int} styleP     : style of widget
     * @return {IWidget*}       : widget instance
     */
    IWidget* createField(const char* textP, ImFont* pFontP, int styleP, const char* pHintP);

private:
    WidgetFactory();
    /**
     * Setup widget.
     * 
     * @param  {IWidget*} pWidgetP : widget to setup
     * @return {IWidget*}          : same widget as pWidgetP
     */
    IWidget* setupWidget(IWidget* pWidgetP);

    static WidgetFactory* pInstanceM;
    /** Unique indx for widgets */
    Id indexM;
};

} // namespace GUI
