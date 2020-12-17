/**
 * Author: 		Iosif Haidu
 * Description: Implementation of IWidgetFactory
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_WIDGETFACTORY_H__
#define __GUI_WIDGETFACTORY_H__

#include "iwidgetfactory.h"

namespace GUI
{

class WidgetFactory : public IWidgetFactory
{
public:
    /**
     * Get unique instance.
     * @return {IWidgetFactory}  : instance of IWidgetFactory
     */
    static IWidgetFactory& instance();
    
    /** see IWidgetFactory::createWindow() */
    IWindow* createWindow(const char* titleP, WindowFlags flags, Font* pFontP) override;
    
private:
    WidgetFactory() = default;

    static IWidgetFactory* pInstanceM;
};

} // namespace GUI

#endif // __GUI_WIDGETFACTORY_H__