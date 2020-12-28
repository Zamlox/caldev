/**
 * Author: 		Iosif Haidu
 * Description: Interface for window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWINDOW_H__
#define __GUI_IWINDOW_H__

#include "internal/gui/iwidget.h"
#include "internal/gui/imgui/common.h"

namespace GUI
{

class IWindow : public IWidget
{
public:
    virtual ~IWindow() = default;
    /**
     * Get x position of left-top corner.
     * @return {int}  : x value of left-top corner
     */
    virtual int getPosX() const = 0;
    /**
     * Get y position of left-top corner.
     * @return {int}  : y value of left-top corner
     */
    virtual int getPosY() const = 0;
    /**
     * Set porition of left-top corner.
     * @param  {int} x : x value of left-top corner
     * @param  {int} y : y value of left-top corner
     */
    virtual void setPos(int x, int y) = 0;
    /**
     * Get width of window.
     * @return {int}  : window width
     */
    virtual int getWidth() const = 0;
    /**
     * Get height of window.
     * @return {int}  : window height
     */
    virtual int getHeight() const = 0;
    /**
     * Set width and height of window.
     * @param  {int} width  : window width
     * @param  {int} height : window height
     */
    virtual void setSize(int width, int height) = 0;
    /**
     * Get title of window.
     * @return {char*}  : window title
     */
    virtual const char* getTitle() const = 0;
    /**
     * Set title of window.
     * @param  {char*} titleP : window title
     */
    virtual void setTitle(const char* titleP) = 0;
    /**
     * Get window background color.
     * @return {Color}  : window background color.
     */
    virtual Color getBgColor() const = 0;
    /**
     * Set window background color.
     * @param  {Color} const : window background color
     */
    virtual void setBgColor(Color const& rColorP) = 0;
    /**
     * Main window is created by Os and we need to keep track of it.
     * @param  {void*} osWindowP : main window created by Os
     */
    virtual void makeMainWindow(void* osWindowP) = 0;    
};

} // namespace GUI

#endif // __GUI_IWINDOW_H__