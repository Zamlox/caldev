/**
 * Author: 		Iosif Haidu
 * Description: Implementation of IWidgetFactory
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_WIDGETFACTORY_H__
#define __GUI_WIDGETFACTORY_H__

#include "internal/gui/iwidgetfactory.h"

namespace GUI
{

/**
 * Factory for widgets
 */
class WidgetFactory : public IWidgetFactory
{
public:
    /**
     * Get unique instance.
     * @return {IWidgetFactory}  : instance of IWidgetFactory
     */
    static IWidgetFactory& instance();
    
    /** see IWidgetFactory::createWindow() */
    owner<IWindow*> createWindow(czstring<> titleP, int flags, Font* pFontP) override;
    /** see IWidgetFactory::destroyWindow() */
    void destroyWindow(IWindow*& pWindowP) override;
    
private:
    WidgetFactory();

    static IWidgetFactory* pInstanceM;
    /** Unique indx for widgets */
    Id indexM;
};

} // namespace GUI

#endif // __GUI_WIDGETFACTORY_H__