/**
 * Author: 		Iosif Haidu
 * Description: Define and implement a window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IMGUI_WINDOW_H__
#define __GUI_IMGUI_WINDOW_H__

#include "internal/gui/iwindow.h"
#include "internal/gui/basewidget.h"
#include "extern/imgui/imgui_internal.h"
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
     * While rendering window and children we must protect 
     * resurces and operations which might run in parallel
     * with management operations.
     */
    void render() override;

private:
    /** Needed for ImGui::Begin() */
    bool isOpenM;
    /** Window title */
    Title titleM;
    /** Window flags */
    int flagsM;
    /** Window font */
    Font *pFontM;
    /** Reference to OS window if this is main window, nullptr otherwise */
    GLFWwindow* osWindowM;
    /** Flag indicating if render() was called for the first time */
    bool firstTimeRenderM;
    /** A reference to ImGui window */
    ImGuiWindow* pImGuiWindowM;
};

} // namespace ImGui
} // namespace GUI

#endif // __GUI_IMGUI_WINDOW_H__