/**
 * Author: 		Iosif Haidu
 * Description: Define and implement a window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwindow.h"
#include "internal/gui/basewidget.h"
#include "internal/gui/imgui/window.h"

namespace GUI
{

/**
 * Implementation of IWindow
 */
class Window : public Base<IWindow>
{
public:
    /**
     * Initialize window 
     * 
     * @param  {char*} titleP   : window title
     * @param  {int} flagsP     : window flags creation
     * @param  {Font*} pFontP   : font to be used
     */
    Window(const char* titleP, int flagsP, Font* pFontP);

    /** see IWindow::getPosX() */
    int getPosX() const override;
    /** see IWindow::getPosY() */
    int getPosY() const override;
    /** see IWindow::setPos() */
    void setPos(int x, int y) override;
    /** see IWindow::getWidth() */
    int getWidth() const override;
    /** see IWindow::getHeight() */
    int getHeight() const override;
    /** see IWindow::setSize() */
    void setSize(int width, int height) override;
    /** see IWindow::getTitle() */
    const char* getTitle() const override;
    /** see IWindow::setTitle() */
    void setTitle(const char* titleP) override;
    /** see IWindow::getBgColor() */
    Color getBgColor() const override;
    /** see IWindow::setBgColor() */
    void setBgColor(Color const& rColorP) override;
    /** see IWindow::makeMainWindow() */
    void makeMainWindow(not_null<void*> osWindowP) override;
    /**
     * Renders window on screen.
     */
    void render() override;
    /** see IWindow::addChild() */
    void addChild(IWindow& rWindowP) override;
    /** see IWindow::getWindowStorage() */
    void* getWindowStorage() override;

private:
    /** Window implementation for ImGui */
    ImGui::Window implM;
};

} // namespace GUI
