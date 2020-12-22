/**
 * Author: 		Iosif Haidu
 * Description: Interface for creating widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWIDGETFACTORY_H__
#define __GUI_IWIDGETFACTORY_H__

#include "iwidget.h"
#include "iwindow.h"
#include "imgui/common.h"

namespace GUI
{

class IWidgetFactory
{
public:
    virtual ~IWidgetFactory() = default;
    /**
     * Create a window.
     * @param  {char*} titleP       : title of window (can be UTF-8 if backend allows)
     * @param  {int} flags          : flags for creating window 
     * @param  {Font*} pFontP       : font to be used in window
     * @return {IWindow*}           : new window if succeeded or nullptr if failed
     */
    virtual IWindow* createWindow(const char* titleP, int flags, Font* pFontP) = 0;    
    /**
     * Destroy a window.
     * @param  {IWindow*} pWindowP : Window to be destroyed
     */
    virtual void destroyWindow(IWindow*& pWindowP) = 0;
};

} // namespace GUI

#endif // __GUI_IWIDGETFACTORY_H__