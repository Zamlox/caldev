/**
 * Author: 		Iosif Haidu
 * Description: Define and implement a window
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwindow.h"
#include "internal/gui/imgui/window.h"

namespace GUI
{

/**
 * Implementation of IWindow
 */
class Window : public IWindow
{
public:
    /**
     * Initialize window 
     * 
     * @param  {char*} titleP   : window title
     * @param  {int} flagsP     : window flags creation
     * @param  {Font*} pFontP   : font to be used
     */
    Window(const char* titleP, int flagsP, Font* pFontP, Id idP, Id parentIdP);

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

    /** see IRender::beginRender() */
    void beginRender() override;
    /** see IRender::endRender() */
    void endRender() override;

    // resize related
    IResize& getResizeBorder(int indexP) override;
    bool isAlreadyBorderResizing(int& rBorderP) const override;
    IResize& getResizeCorner(int indexP) override;
    bool isAlreadyCornerResizing(int& rCornerP) const override;
    void moveTop(
        ImVec2& rPosTargetP,
        ImVec2& rSizeTargetP,
        ImRect const& visibility_rect,
        ImVec2 const& visibility_padding,
        ImVec2 const& rMousePosP,
        ImVec2 const& rMouseDeltaP,
        int minSizeYP,
        int minOffsYP) override;
    void moveBottom(
        ImVec2& rPosTargetP,
        ImVec2& rSizeTargetP,
        ImRect const& visibility_rect,
        ImVec2 const& rMousePosP,
        ImVec2 const& rMouseDeltaP,
        int maxSizeYP,
        int minOffsYP) override;
    void moveLeft(
        ImVec2& rPosTargetP,
        ImVec2& rSizeTargetP,
        ImRect const& visibility_rect,
        ImVec2 const& visibility_padding,
        ImVec2 const& rMousePosP,
        ImVec2 const& rMouseDeltaP,
        int minSizeXP,
        int minOffsXP) override;
    void moveRight(
        ImVec2& rPosTargetP,
        ImVec2& rSizeTargetP,
        ImRect const& visibility_rect,
        ImVec2 const& rMousePosP,
        ImVec2 const& rMouseDeltaP,
        int maxSizeXP,
        int minOffsXP) override;


    Id getId() const override;
    void setId(Id idP) override;
    void update(GlueFace const& rFaceP) override;

private:
    /** Window implementation for ImGui */
    ImGui::Window implM;
};

} // namespace GUI
