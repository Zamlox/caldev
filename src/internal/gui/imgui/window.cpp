/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "window.h"

namespace GUI
{
namespace ImGui
{

Window::Window(const char* titleP, WindowFlags flagsP, Font* pFontP)
    : isOpenM{true}
    , flagsM{flagsP}
    , pFontM{pFontP}
    , osWindowM{nullptr}
{
    titleM.append(titleP);
}

int Window::getPosX() const
{
    return xM;
}

int Window::getPosY() const
{
    return yM;
}

void Window::setPos(int x, int y)
{
    xM = x;
    yM = y;
}

int Window::getWidth() const
{
    return widthM;
}

int Window::getHeight() const
{
    return heightM;
}

void Window::setSize(int width, int height)
{
    widthM = width;
    heightM = height;
}

const char* Window::getTitle() const
{
    return titleM.c_str();
}

void Window::setTitle(const char* titleP)
{
    titleM.clear();
    titleM.append(titleP);
}

Color Window::getBgColor() const
{
    return bgColorM;
}

void Window::setBgColor(Color const& rColorP)
{
    bgColorM = rColorP;
}

void Window::makeMainWindow(void* osWindowP)
{
    osWindowM = static_cast<GLFWwindow*>(osWindowP);
}

void Window::render()
{
    
}

} // namespace ImGui
} // namespace GUI
