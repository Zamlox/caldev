/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/default.h"
#include "modules/gui/opengl.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"
#include "extern/imgui/imgui_internal.h"
#include "extern/imgui/examples/imgui_impl_opengl2.h"
#include <sstream>
#include <thread>

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
    : pOsWindowM{nullptr}
    , pMainWidgetWindowM{nullptr}
    , stopEngineM{false}
    , fontsM{&syncBeforeFrameStartsM}
    , newFontAddedM{false}
    , isRuningInBkgThreadM{true}
    , engineStartedM{false}
{
}

bool OpenGL::init(bool bkgThreadP)
{
    stopEngineM = false;
    pEngineinstanceM = this;
    if (isRuningInBkgThreadM = bkgThreadP; !isRuningInBkgThreadM)
    {
        return initGuiEngine();
    }
    return true;
}

bool OpenGL::start()
{
    bool result{true};
    PromiseInit isInitReady;
    engineStartedM = true;
    if (isRuningInBkgThreadM)
    {
        engineResultM = std::async(std::launch::async, &OpenGL::guiEngine, this, &isInitReady);
        auto fInitReady = isInitReady.get_future();
        fInitReady.get();
    }
    else
    {
        result = guiEngine();
    }
    
    return result;
}

bool OpenGL::stop()
{
    if (engineStartedM)
    {
        stopEngineM = true;
        if (isRuningInBkgThreadM)
        {
            return engineResultM.get();
        }
        return true;
    }
    return false;
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
        glfwSetWindowPos(pOsWindowM, xP, yP);
        glfwSetWindowSize(pOsWindowM, widthP, heightP);
        glfwSetWindowTitle(pOsWindowM, titleP);
        glfwSetWindowSizeLimits(pOsWindowM, MIN_SIZE_X, MIN_SIZE_X, GLFW_DONT_CARE, GLFW_DONT_CARE);
        (visibleP) ? glfwShowWindow(pOsWindowM) : glfwHideWindow(pOsWindowM);
        if (pMainWidgetWindowM == nullptr)
        {
            pMainWidgetWindowM = WidgetFactory::instance().createWindow(
                titleP
                , WindowFlags_NoNav
                | WindowFlags_NoDecoration
                | WindowFlags_NoBringToFrontOnFocus
                | WindowFlags_NoBorder
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
                //TODO: windowsM.add(pMainWidgetWindowM.get());
                return pMainWidgetWindowM->getId();
            }
        }
        else
        {
            return pMainWidgetWindowM->getId();
        }
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

void OpenGL::showMainWindow()
{
    if (pOsWindowM)
    {
        glfwShowWindow(pOsWindowM);
    }
}

bool OpenGL::initGuiEngine()
{
    // Setup window
    if (glfwSetErrorCallback(glfw_error_callback); !glfwInit())
    {
        exit(1);
    }

    // initialize glfw
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (pOsWindowM = glfwCreateWindow(640, 480, "Dummy", nullptr, nullptr); !pOsWindowM)
    {
        fprintf(stderr, "glfwCreateWindow() error.\n");
        exit(1);
    }
    glfwMakeContextCurrent(pOsWindowM);
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

    //ImGuiIO& io = ::ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer bindings
    InitFor3DRender(pOsWindowM, true);

    return true;
}

bool OpenGL::guiEngine(PromiseInit* pInitReadyP)
{
    if (isRuningInBkgThreadM)   
    {
        if (!initGuiEngine())
        {
            return false;
        }

        assert(pInitReadyP);
        pInitReadyP->set_value(true);
    }

    glfwSetWindowSizeCallback(pOsWindowM, OpenGL::size_callback);
    while (!glfwWindowShouldClose(pOsWindowM) && !stopEngineM)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        //glfwWaitEvents();
        glfwPollEvents();

        draw();
    }
    glfwDestroyWindow(pOsWindowM);
    pOsWindowM = nullptr;
    glfwTerminate();
    WidgetFactory::instance().destroyWindow(pMainWidgetWindowM);

    return true;
}

void OpenGL::mainWindowRender()
{
    if (pMainWidgetWindowM)
    {
        pMainWidgetWindowM->render();
    }
}

void OpenGL::draw()
{
    assert(pOsWindowM);

    const std::lock_guard<Mutex> lock{syncBeforeFrameStartsM};

    if (newFontAddedM)
    {
        ImGui_ImplOpenGL2_InvalidateFont();
        newFontAddedM = false;
    }
    // Start Dear ImGui frame
    InitNewFrame();
    ::ImGui::NewFrame();

    // Display widgets here
    // It's enough to render only main window object. The render function
    //  will recursively render its children.
    mainWindowRender();

    // Uncomment below to display FPS in title bar.
    //std::stringstream ss;
    //ss << "Application average " << 1000.0f / ImGui::GetIO().Framerate << " ms/frame (" << ImGui::GetIO().Framerate << " FPS)";
    //glfwSetWindowTitle(pOsWindowM, ss.str().c_str());

    // Rendering
    ::ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(pOsWindowM, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImVec4 clearColor = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
    if (pMainWidgetWindowM)
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
    OpenGL::pEngineinstanceM->draw();
}

Font* OpenGL::createFont(Bind::Rebol2::FaceFont const& rFontP)
{
    Font* pFont{nullptr};
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    Bind::Rebol2::FontInfo fontInfo;
    Bind::Rebol2::Text const& fontName{rFontP.fontPathM};
    if (auto found = fontsM.get(fontName, fontInfo); !found || (found && (fontInfo.faceFontM != rFontP)))
    {
        static ImFontConfig fntConfig;
        const std::lock_guard<Mutex> lock{syncBeforeFrameStartsM};
        pFont = pImGuiContext->IO.Fonts->AddFontFromFileTTF(
            fontName.c_str()
            , rFontP.sizeM.getValueOrDefault(Bind::Rebol2::getDefaultFontSize())
            , &fntConfig
        );
        fontInfo.faceFontM = rFontP;
        fontInfo.pFontM = pFont;
        fontsM.add(fontName, fontInfo);
        newFontAddedM = true;
    }
    else
    {
        pFont = fontInfo.pFontM;
    }
    
    return pFont;
}

} // namespace GUI