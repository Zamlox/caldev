/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/imgui/window.h"
#include "extern/imgui/imgui.h"

namespace GUI
{
namespace ImGui
{

Window::Window(const char* titleP, int flagsP, Font* pFontP)
    : isOpenM{true}
    , flagsM{flagsP}
    , pFontM{pFontP}
    , osWindowM{nullptr}
    , firstTimeRenderM{false}
    , pImGuiWindowM{nullptr}
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

void Window::makeMainWindow(not_null<void*> osWindowP)
{
    osWindowM = static_cast<GLFWwindow*>(osWindowP.get());
    ImGuiContext* pContext = ::ImGui::GetCurrentContext();
    pContext->Extension.mainSize.x = widthM;
    pContext->Extension.mainSize.y = heightM;
}

void Window::beginRender()
{
    if (visibleM && isOpenM)
    {
        // initialize window attributes
        if (firstTimeRenderM)
        {
            // initialize attributes only for first time
            ::ImGui::SetNextWindowPos(ImVec2(xM, yM));
            ::ImGui::SetNextWindowSize(ImVec2{static_cast<float>(widthM), static_cast<float>(heightM)});
        }
        if (pImGuiWindowM)
        {
            // update values which are used inside ImGui::Begin()
            widthM = pImGuiWindowM->Size.x;
            heightM = pImGuiWindowM->Size.y;
            xM = pImGuiWindowM->Pos.x;
            yM = pImGuiWindowM->Pos.y;
        }
        // set color and alpha
        unsigned int bgColor = ::ImGui::ColorConvertFloat4ToU32(bgColorM);
        ::ImGui::SetNextWindowBgColor(bgColor);
        ::ImGui::SetNextWindowBgAlpha(((bgColor & IM_COL32_A_MASK) >> IM_COL32_A_SHIFT) / 255.0);
        // set extra id
        ::ImGui::SetNextWindowExtraId(idM);
        // set font
        if (pFontM) ::ImGui::PushFont(pFontM);
        // create window
        if (!::ImGui::Begin(titleM.c_str(), &isOpenM, flagsM))
        {
            fprintf(stderr, "Cannot create window: %s, %ud\n", titleM.c_str(), flagsM);
            exit(1);
        }
        // get ImGui window for further references
        if (firstTimeRenderM)
        {
            firstTimeRenderM = false;
            pImGuiWindowM = ::ImGui::GetCurrentWindow();
        }

        // move position and resize for ImGui main window as user interacts
        //  with os main window
        if (osWindowM)
        {
            ImGuiContext* pContext = ::ImGui::GetCurrentContext();
            pContext->Extension.pImguiMainWindow = ::ImGui::GetCurrentWindow();
            ::ImGui::SetWindowPos(titleM.c_str(), ImVec2(xM, yM));
            ::ImGui::SetWindowSize(titleM.c_str(), pContext->Extension.mainSize);        
        }
    }
    else if (!isOpenM && osWindowM)
    {
        glfwSetWindowShouldClose(osWindowM, true);
    }
}

void Window::endRender()
{
    if (visibleM && isOpenM)
    {
        // End window
        ::ImGui::End();
        if (pFontM) ::ImGui::PopFont();    
    }
}

} // namespace ImGui
} // namespace GUI
