/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "common.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

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

} // namespace GUI