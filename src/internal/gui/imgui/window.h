/**
 * Author: 		Iosif Haidu
 * Description: Define and implement a window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IMGUI_WINDOW_H__
#define __GUI_IMGUI_WINDOW_H__

#include "iwindow.h"
#include "basewidget.h"
#include <GLFW/glfw3.h>

namespace GUI
{
namespace ImGui
{

/**
 * Implementation of IWindow
 */
class Window : Base<IWindow>
{
public:
    /**
     * Initialize window.
     * 
     * @param  {char*} titleP       : window title
     * @param  {WindowFlags} flagsP : window flags creation
     * @param  {Font*} pFontP       : font to be used
     */
    Window(const char* titleP, WindowFlags flagsP, Font* pFontP);

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
    void makeMainWindow(void* osWindowP) override;
    /**
     * Renders window on screen.
     */
    void render() override;

private:
    /** Needed for ImGui::Begin() */
    bool isOpenM;
    /** Window title */
    Title titleM;
    /** Window flags */
    WindowFlags flagsM;
    /** Window font */
    Font *pFontM;
    /** Reference to OS window if this is main window, nullptr otherwise */
    GLFWwindow* osWindowM;
};

} // namespace ImGui
} // namespace GUI

#endif // __GUI_IMGUI_WINDOW_H__