/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "opengl.h"
#include "widgetfactory.h"
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
    , pOsWindowM{nullptr}
    , stopEngineM{false}
{
    
}

bool OpenGL::start()
{
    return threadM.start();
}

bool OpenGL::stop()
{
    stopEngineM = true;
    return true;
}

int OpenGL::createMainWindow(char const* titleP, int xP, int yP, int widthP, int heightP, int bgColorP)
{
    if (pOsWindowM)
    {
        glfwSetWindowPos(pOsWindowM, xP, yP);
        glfwSetWindowSize(pOsWindowM, widthP, heightP);
        glfwSetWindowTitle(pOsWindowM, titleP);
        glfwSetWindowSizeLimits(pOsWindowM, MIN_SIZE_X, MIN_SIZE_X, GLFW_DONT_CARE, GLFW_DONT_CARE);
        pMainWidgetWindowM.reset(WidgetFactory::instance().createWindow(
            titleP
            , WindowFlags_NoNav
            | WindowFlags_NoDecoration
            | WindowFlags_NoBringToFrontOnFocus
            | WindowFlags_NoBorder
            , nullptr
        ));
        if (pMainWidgetWindowM.get())
        {
            pMainWidgetWindowM->setPos(0, 0);
            pMainWidgetWindowM->setSize(
                (widthP < MIN_SIZE_X) ? MIN_SIZE_X : widthP, 
                (heightP < MIN_SIZE_Y) ? MIN_SIZE_Y : heightP
            );
            pMainWidgetWindowM->setBgColor(::ImGui::ColorConvertU32ToFloat4(bgColorP));
            pMainWidgetWindowM->makeMainWindow(pOsWindowM);
            //TODO: windowsM.add(pMainWidgetWindowM.get());
        }
        glfwShowWindow(pOsWindowM);
        return pMainWidgetWindowM->getId();
    }
    return INVALID_WIDGET_ID;
}

void OpenGL::hideMainWindow()
{
    if (pOsWindowM)
    {
        glfwHideWindow(pOsWindowM);
    }
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
    if (pOpenGL->pOsWindowM = glfwCreateWindow(640, 480, "Rebsdev", nullptr, nullptr); !pOpenGL->pOsWindowM)
    {
        fprintf(stderr, "glfwCreateWindow() error.\n");
        exit(1);
    }
    glfwMakeContextCurrent(pOpenGL->pOsWindowM);
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

    ImGuiIO& io = ::ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer bindings
    InitFor3DRender(pOpenGL->pOsWindowM, true);

    return nullptr;
}

void* OpenGL::guiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);

    glfwSetWindowSizeCallback(pOpenGL->pOsWindowM, OpenGL::size_callback);
    while (!glfwWindowShouldClose(pOpenGL->pOsWindowM) && !pOpenGL->stopEngineM)
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
    glfwDestroyWindow(pOpenGL->pOsWindowM);
    glfwTerminate();

    return nullptr;
}

void OpenGL::mainWindowRender()
{
    if (pMainWidgetWindowM.get())
    {
        pMainWidgetWindowM->render();
    }
}

void OpenGL::draw()
{
    assert(pOsWindowM);

    // TODO: invalidate fonts
    // ...

    // Start the Dear ImGui frame
    InitNewFrame();
    ::ImGui::NewFrame();

    // Display widgets here
    // It's enough to render only main window object. The render function
    //  will recursively render its children. 'windowsM' and 'widgetsM' are
    //  intended for fast searching items based on their id, not to render.
    mainWindowRender();

    // Rendering
    ::ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(pOsWindowM, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImVec4 clearColor = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
    if (pMainWidgetWindowM.get())
    {
        clearColor = pMainWidgetWindowM->getBgColor();
    }
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderDrawData(::ImGui::GetDrawData());

    glfwMakeContextCurrent(pOsWindowM);
    glfwSwapBuffers(pOsWindowM);
}

void OpenGL::size_callback(GLFWwindow* window, int width, int height)
{
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    pImGuiContext->Extension.mainSize = ImVec2{static_cast<float>(width), static_cast<float>(height)};
}

} // namespace GUI