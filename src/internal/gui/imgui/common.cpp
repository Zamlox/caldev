/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/imgui/common.h"
#include "extern/imgui/examples/imgui_impl_glfw.h"
#include "extern/imgui/examples/imgui_impl_opengl2.h"

namespace GUI
{

bool InitFor3DRender(GLFWwindow* window, bool install_callbacks)
{
    if (ImGui_ImplGlfw_InitForOpenGL(window, install_callbacks))
    {
        return ImGui_ImplOpenGL2_Init();
    }
    return false;
}

void InitNewFrame()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void RenderDrawData(void* pDataP)
{
    ImGui_ImplOpenGL2_RenderDrawData(static_cast<ImDrawData*>(pDataP));
}

} // namespace GUI