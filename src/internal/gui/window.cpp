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
    implM.setSize(width, heightM);
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

void Window::render()
{
    implM.render();
}

void Window::addChild(IWindow& rWindowP)
{
    implM.addChild(rWindowP);
}

void* Window::getWindowStorage()
{
    return implM.getWindowStorage();
}

} // namespace GUI