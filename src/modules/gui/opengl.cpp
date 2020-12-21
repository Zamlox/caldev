/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "opengl.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui/common.h"

namespace GUI
{

namespace 
{
    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }
} // anonymous namespace

OpenGL::OpenGL()
    : threadM{"GuiEngine", &OpenGL::initGuiEngine, &OpenGL::guiEngine, this}
    , pMainWindowM{nullptr}
{
    
}

bool OpenGL::start()
{
    return threadM.start();
}

bool OpenGL::stop()
{
    return true;
}

void* OpenGL::initGuiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);

    // Setup window
    if (glfwSetErrorCallback(glfw_error_callback); !glfwInit())
    {
        exit(1);
    }

    // initialize glfw
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (pOpenGL->pMainWindowM = glfwCreateWindow(640, 480, "Rebsdev", nullptr, nullptr); !pOpenGL->pMainWindowM)
    {
        fprintf(stderr, "glfwCreateWindow() error.\n");
        exit(1);
    }
    glfwMakeContextCurrent(pOpenGL->pMainWindowM);
    glfwSwapInterval(1);

    ImGuiContext* pImGuiContext = ::ImGui::CreateContext();
    // TODO: pImGuiContext->Extension.fontsUsed = &self->fontsM;

    // Initial styling
    // Setup Dear ImGui style
    ::ImGui::StyleColorsNative();
    pImGuiContext->Style.WindowRounding = 0.0f;
    pImGuiContext->Style.WindowPadding = ImVec2{0.0, 0.0};

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    // set main storages in ImGuiContext
    // pImGuiContext->Extension.pMainWindowStorage = &self->windowsM;
    // pImGuiContext->Extension.pMainWidgetStorage = &self->widgetsM;

    ImGuiIO& io = ::ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer bindings
    InitFor3DRender(pOpenGL->pMainWindowM, true);

    return nullptr;
}

void* OpenGL::guiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);

    glfwSetWindowSizeCallback(pOpenGL->pMainWindowM, OpenGL::size_callback);
    while (!glfwWindowShouldClose((pOpenGL->pMainWindowM)))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        //glfwWaitEvents();
        glfwPollEvents();

        pOpenGL->draw();
    }
    glfwDestroyWindow(pOpenGL->pMainWindowM);
    glfwTerminate();

    return nullptr;
}

void OpenGL::draw()
{
    
}

void OpenGL::size_callback(GLFWwindow* window, int width, int height)
{
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    pImGuiContext->Extension.mainSize = ImVec2{static_cast<float>(width), static_cast<float>(height)};
}

} // namespace GUI