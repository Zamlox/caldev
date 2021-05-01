/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/window.h"

namespace GUI
{

Window::Window(const char* titleP, int flagsP, Font* pFontP)
    : implM{titleP, flagsP, pFontP}
{
}

int Window::getPosX() const
{
    return implM.getPosX();
}

int Window::getPosY() const
{
    return implM.getPosY();
}

void Window::setPos(int x, int y)
{
    implM.setPos(x, y);
}

int Window::getWidth() const
{
    return implM.getWidth();
}

int Window::getHeight() const
{
    return implM.getHeight();
}

void Window::setSize(int width, int height)
{
    implM.setSize(width, height);
}

const char* Window::getTitle() const
{
    return implM.getTitle();
}

void Window::setTitle(const char* titleP)
{
    implM.setTitle(titleP);
}

Color Window::getBgColor() const
{
    return implM.getBgColor();
}

void Window::setBgColor(Color const& rColorP)
{
    implM.setBgColor(rColorP);
}

void Window::makeMainWindow(not_null<void*> osWindowP)
{
    implM.makeMainWindow(osWindowP);
}

void Window::beginRender()
{
    implM.beginRender();
}

void Window::endRender()
{
    implM.endRender();
}

IResize& Window::getResizeBorder(int indexP)
{
    return implM.getResizeBorder(indexP);
}

bool Window::isAlreadyBorderResizing(int& rBorderP) const
{
    return implM.isAlreadyBorderResizing(rBorderP);
}

IResize& Window::getResizeCorner(int indexP)
{
    return implM.getResizeCorner(indexP);
}

bool Window::isAlreadyCornerResizing(int& rCornerP) const
{
    return implM.isAlreadyCornerResizing(rCornerP);
}

void Window::moveTop(
    ImVec2& rPosTargetP,
    ImVec2& rSizeTargetP,
    ImRect const& visibility_rect,
    ImVec2 const& visibility_padding,
    ImVec2 const& rMousePosP,
    ImVec2 const& rMouseDeltaP,
    int minSizeYP,
    int minOffsYP)
{
    implM.moveTop(rPosTargetP, rSizeTargetP, visibility_rect, visibility_padding, rMousePosP, rMouseDeltaP, minSizeYP, minOffsYP);
}

void Window::moveBottom(
    ImVec2& rPosTargetP,
    ImVec2& rSizeTargetP,
    ImRect const& visibility_rect,
    ImVec2 const& rMousePosP,
    ImVec2 const& rMouseDeltaP,
    int maxSizeYP,
    int minOffsYP)
{
    implM.moveBottom(rPosTargetP, rSizeTargetP, visibility_rect, rMousePosP, rMouseDeltaP, maxSizeYP, minOffsYP);
}

void Window::moveLeft(
    ImVec2& rPosTargetP,
    ImVec2& rSizeTargetP,
    ImRect const& visibility_rect,
    ImVec2 const& visibility_padding,
    ImVec2 const& rMousePosP,
    ImVec2 const& rMouseDeltaP,
    int minSizeXP,
    int minOffsXP)
{
    implM.moveLeft(rPosTargetP, rSizeTargetP, visibility_rect, visibility_padding, rMousePosP, rMouseDeltaP, minSizeXP, minOffsXP);
}

void Window::moveRight(
    ImVec2& rPosTargetP,
    ImVec2& rSizeTargetP,
    ImRect const& visibility_rect,
    ImVec2 const& rMousePosP,
    ImVec2 const& rMouseDeltaP,
    int maxSizeXP,
    int minOffsXP)
{
    implM.moveRight(rPosTargetP, rSizeTargetP, visibility_rect, rMousePosP, rMouseDeltaP, maxSizeXP, minOffsXP);
}

Id Window::getId() const
{
    return implM.getId();
}

void Window::setId(Id idP)
{
    implM.setId(idP);
}

void Window::update(GlueFace const& rFaceP)
{
    implM.update(rFaceP);
}

} // namespace GUI