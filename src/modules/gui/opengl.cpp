/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"
#include "modules/gui/opengl.h"
#include "internal/errors/errors.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/widgetfactory.h"
#include "internal/os/util.h"
#include "extern/imgui/imgui.h"
#include "extern/imgui/imgui_internal.h"
#include "extern/imgui/examples/imgui_impl_opengl2.h"
#include "extern/imgui/examples/imgui_impl_glfw.h"
extern "C" {
#include "extern/rebsdev/src/glue/face/face.h"
}
#include <sstream>

extern "C" FaceFont gDefaultFont;

namespace GUI
{

namespace 
{
    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }
} // anonymous namespace

owner<OpenGL*> OpenGL::pEngineinstanceM{nullptr};

OpenGL::OpenGL()
    : threadM{"GuiEngine", &OpenGL::initGuiEngine, &OpenGL::guiEngine, this}
    , pOsWindowM{nullptr}
    , pMainWidgetWindowM{nullptr}
    , stopEngineM{false}
    , isRuningInBkgThreadM{true}
    , rendererM{syncBeforeFrameStartsM}
    , mainWindowVisibilityM{false}
    , isFirstTimeRenderM{true}
{
    ::ImGui::createLog();
}

bool OpenGL::init(bool bkgThreadP)
{
    stopEngineM = false;
    pEngineinstanceM = this;
    if (isRuningInBkgThreadM = bkgThreadP; !isRuningInBkgThreadM)
    {
        initGuiEngine(this);
    }
    return true;
}

bool OpenGL::startOnThread()
{
    if (isRuningInBkgThreadM)
    {
        return threadM.start();
    }
    return false;
}

bool OpenGL::startOnMainThread()
{
    if (!isRuningInBkgThreadM)
    {
        guiEngine(this);
        return true;
    }
    return false;
}

bool OpenGL::stop()
{
    stopEngineM = true;
    threadM.join();
    return true;
}

int OpenGL::createMainWindow(
    czstring<> titleP, 
    int xP, int yP, 
    int widthP, 
    int heightP, 
    int bgColorP,
    bool visibleP)
{
    if (pOsWindowM)
    {
        mainWindowVisibilityM = visibleP;
        glfwSetWindowPos(pOsWindowM, xP, yP);
        glfwSetWindowSize(pOsWindowM, widthP, heightP);
        glfwSetWindowTitle(pOsWindowM, titleP);
        glfwSetWindowSizeLimits(pOsWindowM, MIN_SIZE_X, MIN_SIZE_X, GLFW_DONT_CARE, GLFW_DONT_CARE);
        if (pMainWidgetWindowM == nullptr)
        {
            pMainWidgetWindowM = WidgetFactory::instance().createWindow(
                titleP
                //, WindowFlags_None
                , WindowFlags_NoNav
                | WindowFlags_NoDecoration
                | WindowFlags_NoBringToFrontOnFocus
                | WindowFlags_NoBorder
                | WindowFlags_NoResize
                | WindowFlags_NoMove
                , nullptr
            );
            if (pMainWidgetWindowM)
            {
                pMainWidgetWindowM->setPos(0, 0);
                pMainWidgetWindowM->setSize(
                    (widthP < MIN_SIZE_X) ? MIN_SIZE_X : widthP, 
                    (heightP < MIN_SIZE_Y) ? MIN_SIZE_Y : heightP
                );
                pMainWidgetWindowM->setBgColor(::ImGui::ColorConvertU32ToFloat4(bgColorP));
                pMainWidgetWindowM->makeMainWindow(pOsWindowM);
                rendererM.addMainWindow(pMainWidgetWindowM);
                return pMainWidgetWindowM->getId();
            }
        }
        else
        {
            return pMainWidgetWindowM->getId();
        }
    }
    return ERR_GUI_MAIN_WINDOW_FAILED;
}

void OpenGL::hideMainWindow()
{
    if (pOsWindowM)
    {
        glfwHideWindow(pOsWindowM);
    }
}

void OpenGL::showMainWindow()
{
    if (pOsWindowM)
    {
        glfwShowWindow(pOsWindowM);
    }
}

Id OpenGL::createWidget(const char* pFaceDescriptionP)
{
    return rendererM.createWidget(pFaceDescriptionP, Api::GuiType::GUI_OPENGL2);
}

void OpenGL::stash()
{
    rendererM.stash();
}

void OpenGL::unstash()
{
    rendererM.unstash();
}

void* OpenGL::initGuiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);

    // Setup window
    if (glfwSetErrorCallback(glfw_error_callback); !glfwInit())
    {
        fprintf(stderr, "glfwInit() error.\n");
        exit(1);
    }

    // initialize glfw
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (pOpenGL->pOsWindowM = glfwCreateWindow(640, 480, "Dummy", nullptr, nullptr); !pOpenGL->pOsWindowM)
    {
        fprintf(stderr, "glfwCreateWindow() error.\n");
        exit(1);
    }
    glfwMakeContextCurrent(pOpenGL->pOsWindowM);
    glfwSwapInterval(0);

    ImGuiContext* pImGuiContext = ::ImGui::CreateContext();
    // TODO: pImGuiContext->Extension.fontsUsed = &self->fontsM;    - is it needed ???

    // Initial styling
    // Setup Dear ImGui style
    ::ImGui::StyleColorsNative();
    pImGuiContext->Style.WindowRounding = 0.0f;
    pImGuiContext->Style.WindowPadding = ImVec2{0.0, 0.0};

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    // set main storages in ImGuiContext
    pImGuiContext->Extension.pMainWindowStorage = &pOpenGL->rendererM;

    //ImGuiIO& io = ::ImGui::GetIO();
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
    // Cleanup
    pOpenGL->pOsWindowM = nullptr;
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(pOpenGL->pOsWindowM);
    glfwTerminate();

    return nullptr;
}

void OpenGL::draw()
{
    assert(pOsWindowM);

    syncBeforeFrameStartsM.lock();

    if (rendererM.getNewFontAdded())
    {
        ImGui_ImplOpenGL2_InvalidateFont();
        rendererM.setNewFontAdded(false);
    }
    // Start Dear ImGui frame
    InitNewFrame();
    ::ImGui::NewFrame();

    // Uncomment below to display FPS in title bar.
    //std::stringstream ss;
    //ss << "Application average " << 1000.0f / ImGui::GetIO().Framerate << " ms/frame (" << ImGui::GetIO().Framerate << " FPS)";
    //glfwSetWindowTitle(pOsWindowM, ss.str().c_str());

    // Display main window
    if (pMainWidgetWindowM)
    {
        // Display widgets
        rendererM.render();
    }

    // Rendering
    ::ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(pOsWindowM, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImVec4 clearColor = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
    if (pMainWidgetWindowM)
    {
        //clearColor = pMainWidgetWindowM->getBgColor();
    }
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderDrawData(::ImGui::GetDrawData());

    glfwMakeContextCurrent(pOsWindowM);
    glfwSwapBuffers(pOsWindowM);

    syncBeforeFrameStartsM.unlock();

    if (rendererM.isInitialUnstash() && isFirstTimeRenderM)
    {
        isFirstTimeRenderM = false;
        if (mainWindowVisibilityM)
            showMainWindow();
    }
}

void OpenGL::size_callback(GLFWwindow* window, int width, int height)
{
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    pImGuiContext->Extension.mainSize = ImVec2{static_cast<float>(width), static_cast<float>(height)};
    //OpenGL::pEngineinstanceM->draw();
}

} // namespace GUI