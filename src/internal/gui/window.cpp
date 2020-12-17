/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "window.h"

namespace GUI
{

Window::Window(const char* titleP, WindowFlags flagsP, Font* pFontP)
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

void Window::makeMainWindow(void* osWindowP)
{
    implM.makeMainWindow(osWindowP);
}

void Window::render()
{
    implM.render();
}

} // namespace GUI