/**
 * Author: 		Iosif Haidu
 * Description: Interface for creating widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/iwindow.h"
#include "internal/gui/imgui/common.h"
#include <gsl/pointers.h>
#include <gsl/string_span.h>

namespace GUI
{

using namespace gsl;

class IWidgetFactory
{
public:
    virtual ~IWidgetFactory() = default;
    /**
     * Create a window.
     * @param  {czstring} titleP    : title of window (can be UTF-8 if backend allows)
     * @param  {int} flags          : flags for creating window 
     * @param  {Font*} pFontP       : font to be used in window
     * @return {IWindow*}           : new window if succeeded or nullptr if failed
     */
    virtual owner<IWindow*> createWindow(czstring<> titleP, int flags, Font* pFontP) = 0;    
    /**
     * Destroy a window.
     * @param  {IWindow*} pWindowP : Window to be destroyed
     */
    virtual void destroyWindow(owner<IWindow*>& pWindowP) = 0;
};

} // namespace GUI
