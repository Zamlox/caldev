/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/imgui/window.h"
#include "extern/imgui/imgui.h"

#include "internal/gui/widgets/image.h"

namespace GUI
{
namespace ImGui
{

Window::Window(const char* titleP, int flagsP, Font* pFontP, Id idP, Id parentIdP)
    : isOpenM{true}
    , flagsM{flagsP}
    , pFontM{pFontP}
    , fontPushedM{false}
    , osWindowM{nullptr}
    , firstTimeRenderM{true}
    , pImGuiWindowM{nullptr}
{
    idM = idP;
    parentIdM = parentIdP;
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
        //::ImGui::SetNextWindowExtraId(idM);
        // set font
        if (pFontM)
        {
            fontPushedM = true;
            ::ImGui::PushFont(pFontM);
        }
        // create window
        ::ImGui::Begin(titleM.c_str(), &isOpenM, flagsM, &idM, (parentIdM != PARENT_NONE) ? &parentIdM : nullptr);
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
            // =======================
            // DEBUG
            // create log widget
            float logHeight{200.0};
            ::ImGui::createLogArea(0, heightM - logHeight, widthM, logHeight);
            //Widget::Image img(Api::GuiType::GUI_OPENGL2, "D:\\Pictures\\test.png", 0);
            // =======================
        }
    }
    else if (!isOpenM && osWindowM)
    {
        glfwSetWindowShouldClose(osWindowM, true);
    }
}

void Window::endRender()
{
    if (visibleM)
    {
        visibleM = isOpenM;
        if (fontPushedM)
        {
            fontPushedM = false;
            ::ImGui::PopFont();    
        }
        // End window
        ::ImGui::End();
    }
}

IResize& Window::getResizeBorder(int indexP)
{
    return resizeBordersM[indexP];
}

bool Window::isAlreadyBorderResizing(int& rBorderP) const
{
    rBorderP = -1;
    for (int i = 0; i < COUNT_BORDERS; i++)
    {
        if (resizeBordersM[i].getStarted())
        {
            rBorderP = i;
            return true;
        }
    }
    return false;
}

IResize& Window::getResizeCorner(int indexP)
{
    return resizeCornersM[indexP];
}

bool Window::isAlreadyCornerResizing(int& rCornerP) const
{
    rCornerP = -1;
    for (int i = 0; i < COUNT_CORNERS; i++)
    {
        if (resizeCornersM[i].getStarted())
        {
            rCornerP = i;
            return true;
        }
    }
    return false;
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
    // printf("Pos: (%f, %f), vis_rect: MousePos: (%f, %f), Max(%f, %f), Title height: %f\n\r", pImGuiWindowM->Pos.x, pImGuiWindowM->Pos.y, rMousePosP.x, rMousePosP.y, visibility_rect.Max.x, visibility_rect.Max.y, pImGuiWindowM->TitleBarHeight());
    if (rMousePosP.y - rMouseDeltaP.y <= visibility_rect.Max.y)
    {
        if ((rSizeTargetP.y > minSizeYP) || (rMousePosP.y <= rPosTargetP.y))
        {
            if (rMousePosP.y - rMouseDeltaP.y + minSizeYP > rPosTargetP.y + rSizeTargetP.y)
                rPosTargetP.y = rPosTargetP.y + rSizeTargetP.y - minSizeYP ;
            else
                rPosTargetP.y = rMousePosP.y - rMouseDeltaP.y;
            if (rPosTargetP.y < minOffsYP)
            {
                // when drag top out of border stop at MIN_OFFS_BORDER
                rPosTargetP.y = minOffsYP;
                rSizeTargetP.y = yM + heightM - minOffsYP;
            }
            else
                // otherwise enlarge window
                rSizeTargetP.y = yM + heightM - rPosTargetP.y;
        }
    }
    else
    {
        if (rPosTargetP.y + rSizeTargetP.y >= visibility_rect.Max.y + visibility_padding.y)
            rPosTargetP.y = visibility_rect.Max.y;
    }
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
    if (rMousePosP.y + rMouseDeltaP.y >= visibility_rect.Min.y)
    {
        if (rMousePosP.y > maxSizeYP)
            rSizeTargetP.y = maxSizeYP - yM - minOffsYP;
        else
            rSizeTargetP.y = rMousePosP.y - yM + rMouseDeltaP.y;
    }
    else
    {
        rSizeTargetP.y = visibility_rect.Min.y - rPosTargetP.y;
    }
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
    if (rMousePosP.x - rMouseDeltaP.x <= visibility_rect.Max.x)
    {
        if ((rSizeTargetP.x > minSizeXP) || (rMousePosP.x < rPosTargetP.x))
        {
            if (rMousePosP.x - rMouseDeltaP.x + minSizeXP > rPosTargetP.x + rSizeTargetP.x)
                rPosTargetP.x = rPosTargetP.x + rSizeTargetP.x - minSizeXP;
            else
                rPosTargetP.x = rMousePosP.x - rMouseDeltaP.x;
            if (rPosTargetP.x < minOffsXP)
            {
                // when drag left out of border stop at minOffsXP
                rPosTargetP.x = minOffsXP;
                rSizeTargetP.x = xM + widthM - minOffsXP;
            }
            else
                // otherwise enlarge window
                rSizeTargetP.x = xM + widthM - rPosTargetP.x;
        }
    }
    else
    {
        if (rPosTargetP.x + rSizeTargetP.x > visibility_rect.Max.x + visibility_padding.x)
            rPosTargetP.x = visibility_rect.Max.x;
    }
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
    if (rMousePosP.x + rMouseDeltaP.x >= visibility_rect.Min.x)
    {
        if (rMousePosP.x > maxSizeXP)
            rSizeTargetP.x = maxSizeXP - xM - minOffsXP;
        else
            rSizeTargetP.x = rMousePosP.x - xM + rMouseDeltaP.x;
    }
    else
    {
        rSizeTargetP.x = visibility_rect.Min.x - rPosTargetP.x;
    }
}

} // namespace ImGui
} // namespace GUI
