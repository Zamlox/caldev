/**
 * Author: 		Iosif Haidu
 * Description: GUI engine implementation based on OpenGL 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"
#include "modules/gui/igui.h"
#include "internal/os/thread.h"
#include "internal/os/mutex.h"
#include "internal/gui/iwindow.h"
#include "internal/gui/imgui/common.h"
#include "bindings/rebol2/cpp/font.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace GUI
{

/**
 * GUI engine implementing IGui
 */
class OpenGL : public IGui
{
public:
    OpenGL();
    /** see IGui::init() */
    bool init(bool bkgThreadP) override;
    /** see IGui::startOnThread() */
    bool startOnThread() override;
    /** see IGui::startOnMainThread() */
    bool startOnMainThread() override;
    /** see IGui::stop() */
    bool stop() override;
    /** see IGui::createMainWindow() */
    int  createMainWindow(
        czstring<> titleP, 
        int xP, int yP, 
        int widthP, 
        int heightP, 
        int bgColorP, 
        bool visibleP = true) override;
    /** see IGui::hideMainWindow() */
    void hideMainWindow() override;
    /** see IGui::showMainWindow() */
    void showMainWindow() override;

    /**
     * Create font based on a rebol font object
     * @param  {Bind::Rebol2::Font} const : rebol2 font object
     * @return {Font*}                    : font created if successful or nullptr otherwise
     */
    Font* createFont(Bind::Rebol2::FaceFont const& rFontP);

private:
    /**
     * Code to run before returning back to caller after thread starts
     * @param  {void*} pParamP : pass 'this' to have access to internal data
     */
    static void* initGuiEngine(void* pParamP);
    /**
     * Code to run for GUI engine 
     * @param  {void*} pParamP : pass 'this' to have access to internal data
     */
    static void* guiEngine(void*pParamP);

    /** Renders main window */
    void mainWindowRender();
    /** Draw on canvas */
    void draw();

    /** Callback for size */
    static void size_callback(GLFWwindow* window, int width, int height);

    /** Separate thread to run GUI engine */
    Os::Thread threadM;
    /** Instance of os main window */
    GLFWwindow* pOsWindowM;
    /** Main window widget */
    IWindow* pMainWidgetWindowM;
    /** Flag used to stop the engine */
    bool stopEngineM;
    /** Synchronize operations before a new frame starts */
    Os::Mutex syncBeforeFrameStartsM;
    /** Collection of created fonts */
    Bind::Rebol2::FontsMap fontsM;
    /** Flag indicating new font has been added */
    bool newFontAddedM;
    /** Flag indicating if GUI engine runs in background thread */
    bool isRuningInBkgThreadM;
    /** One instance for one main window  */
    static owner<OpenGL*> pEngineinstanceM;
};

} // namespace GUI