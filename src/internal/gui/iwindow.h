/**
 * Author: 		Iosif Haidu
 * Description: Interface for window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/iresize.h"
#include <gsl/pointers.h>

namespace GUI
{

using namespace gsl;

class IWindow : public IWidget
{
public:
    virtual ~IWindow() = default;

    /**
     *  Clone window.
     * 
     * @return {IWindow*}  : new window instance
     */
    virtual IWindow* clone() = 0;

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
    virtual void makeMainWindow(not_null<void*> osWindowP) = 0;   

    // resize related
    virtual IResize& getResizeBorder(int indexP) = 0;
    virtual bool isAlreadyBorderResizing(int& rBorderP) const = 0;
    virtual IResize& getResizeCorner(int indexP) = 0;
    virtual bool isAlreadyCornerResizing(int& rCornerP) const = 0;
    virtual void moveTop(
            ImVec2& rPosTargetP,
            ImVec2& rSizeTargetP,
            ImRect const& visibility_rect,
            ImVec2 const& visibility_padding,
            ImVec2 const& rMousePosP,
            ImVec2 const& rMouseDeltaP,
            int minSizeYP,
            int minOffsYP) = 0;
    virtual void moveBottom(
            ImVec2& rPosTargetP,
            ImVec2& rSizeTargetP,
            ImRect const& visibility_rect,
            ImVec2 const& rMousePosP,
            ImVec2 const& rMouseDeltaP,
            int maxSizeYP,
            int minOffsYP) = 0;
    virtual void moveLeft(
            ImVec2& rPosTargetP,
            ImVec2& rSizeTargetP,
            ImRect const& visibility_rect,
            ImVec2 const& visibility_padding,
            ImVec2 const& rMousePosP,
            ImVec2 const& rMouseDeltaP,
            int minSizeXP,
            int minOffsXP) = 0;
    virtual void moveRight(
            ImVec2& rPosTargetP,
            ImVec2& rSizeTargetP,
            ImRect const& visibility_rect,
            ImVec2 const& rMousePosP,
            ImVec2 const& rMouseDeltaP,
            int maxSizeXP,
            int minOffsXP) = 0;
};

} // namespace GUI
