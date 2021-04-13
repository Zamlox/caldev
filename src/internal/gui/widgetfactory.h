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
    
    /** see IWidgetFactory::createWindow() */
    owner<IWindow*> createWindow(czstring<> titleP, int flags, Font* pFontP);
    /** see IWidgetFactory::destroyWindow() */
    void destroyWindow(owner<IWindow*>& pWindowP);
    /** see IWidgetFactory::destroyWidget() */
    void destroyWidget(owner<IWidget*>& pWidgetP);

    /** see IWidgetFactory::createLabel() */
    //IWidget* createLabel(const char* textP, ImFont* pFontP);
    
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
