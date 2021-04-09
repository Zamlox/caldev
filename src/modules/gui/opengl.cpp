/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"
#include "modules/gui/opengl.h"
#include "internal/errors/errors.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"
#include "extern/imgui/imgui_internal.h"
#include "extern/imgui/examples/imgui_impl_opengl2.h"
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
    , fontsM{&syncBeforeFrameStartsM}
    , newFontAddedM{false}
    , isRuningInBkgThreadM{true}
{
    
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
    pImGuiContext->Extension.pMainWindowStorage = &pOpenGL->widgetsM;
    // pImGuiContext->Extension.pMainWidgetStorage = &self->widgetsM;

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
    glfwDestroyWindow(pOpenGL->pOsWindowM);
    pOpenGL->pOsWindowM = nullptr;
    glfwTerminate();
    WidgetFactory::instance().destroyWindow(pOpenGL->pMainWidgetWindowM);

    return nullptr;
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

    syncBeforeFrameStartsM.lock();

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

    syncBeforeFrameStartsM.unlock();
}

void OpenGL::size_callback(GLFWwindow* window, int width, int height)
{
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    pImGuiContext->Extension.mainSize = ImVec2{static_cast<float>(width), static_cast<float>(height)};
    OpenGL::pEngineinstanceM->draw();
}

Font* OpenGL::createFont(FaceFont const& rFontP)
{
    Font* pFont{nullptr};
    ImGuiContext* pImGuiContext = ImGui::GetCurrentContext();
    assert(pImGuiContext);
    Bind::Rebol2::FontInfo fontInfo;
    Bind::Rebol2::Text const& fontName{rFontP.path.value};
    if (auto found = fontsM.get(fontName, fontInfo); !found || (found && (fontInfo.faceFontM != rFontP)))
    {
        static ImFontConfig fntConfig;
        syncBeforeFrameStartsM.lock();
        pFont = pImGuiContext->IO.Fonts->AddFontFromFileTTF(
            fontName.c_str()
            , rFontP.size.none ? gDefaultFont.size.value : rFontP.size.value
            , &fntConfig
        );
        fontInfo.faceFontM = rFontP;
        fontInfo.pFontM = pFont;
        fontsM.add(fontName, fontInfo);
        newFontAddedM = true;
        syncBeforeFrameStartsM.unlock();
    }
    else
    {
        pFont = fontInfo.pFontM;
    }
    
    return pFont;
}

Id OpenGL::createWidget(const char* pFaceDescriptionP)
{
    return widgetStub(pFaceDescriptionP, [=](GlueFace const& rFaceP, FaceCounters const& rCountersP){
        return createWidget(rFaceP, rCountersP);
    });
}

Id OpenGL::createWidget(GlueFace const& rFaceP, FaceCounters const& rCountersP)
{
    if (!rFaceP.type.none)
    {
        switch(rFaceP.type.value)
        {
        case TYPE_LABEL:
            break;
        }
    }
    // TODO: draw effect by extracting effect elements using rCountersP.effectCount
    // ...
    return INVALID_WIDGET_ID;
}

bool OpenGL::parseFaceDescription(const char* faceDescriptionP, GlueFace& rFaceP, FaceCounters& rCountersP)
{
    if (void* pBlock; pBlock = parse_block(faceDescriptionP))
    {
        return (get_face_by_index(pBlock, &rFaceP, &rCountersP) == 0);
    }
    return false;
}

Id OpenGL::widgetStub(char const* pFaceDescriptionP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP)
{
    FaceCounters counters; 
    if (GlueFace face; parseFaceDescription(pFaceDescriptionP, face, counters))
    {
        return widgetStub(face, widgetCreatorP, counters);
    }
    return INVALID_WIDGET_ID;
}

Id OpenGL::widgetStub(GlueFace const& rFaceP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP, FaceCounters& rCountersP)
{
    // render widget
    Id result = widgetCreatorP(rFaceP, rCountersP);
    // render widget children if it has
    for (int i = 0; i < rCountersP.paneCount; i++)
    {
        GlueFace* pChild{nullptr};
        GlueFace childFaces;
        if (!rFaceP.pane.none && (get_face_pane_elem((void*)rFaceP.pane.value, i, (void**)&pChild) == SUCCESS) && !pChild->pane.none)
        {
            FaceCounters counters;
            counters.paneCount = get_face_pane_count_by_index((void*)pChild->pane.value, FIELD_PANE, &childFaces);
            void* pChildRaw{nullptr};
            if (get_block_elem(rFaceP.pane.value, i, &pChildRaw) == SUCCESS)
            {
                counters.effectCount = get_face_effect_count_by_index(pChildRaw, FIELD_EFFECT, &childFaces);
                widgetStub(*pChild, widgetCreatorP, counters);
            }
        }
    }
    return result;
}

template <typename T, typename TStorage>
Id OpenGL::createStub(
    GlueFace const& rFaceP, 
    std::function<T*(GlueFace const&)> createP, 
    std::function<void(void)> beforeUpdateP)
{
    Id idWidget{INVALID_WIDGET_ID};
    if (T* pT = createP(rFaceP); pT)
    {
        if (beforeUpdateP)
        {
            beforeUpdateP();
        }
        // TODO: implement update() before calling this function
        // ...
        // pT->update(rFaceP);
        if (!rFaceP.parent.none)
        {
            if (widgetsM.addChildFor(rFaceP.parent.value, pT))
            {
                idWidget = widgetsM.add(pT);
            }
        }
    }
    return idWidget;
}

} // namespace GUI