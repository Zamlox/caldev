/**
 * Author: 		Iosif Haidu
 * Description: GUI engine implementation based on OpenGL 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"
#include "modules/gui/igui.h"
#include "internal/gui/iwindow.h"
#include "internal/gui/imgui/common.h"
#include "bindings/rebol2/cpp/font.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <future>
#include <mutex>

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
    /** see IGui::start() */
    bool start() override;
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
    using PromiseInit = std::promise<bool>;
    using Mutex = std::recursive_mutex;

    /**
     * Initialization code to be executed in same thread as the engine.
     * 
     * @return {bool}   : true if success, false otherwise
     */
    bool initGuiEngine();
    /**
     * Code to run for GUI engine. 
     * Calls initGuiEngine().
     * 
     * @param  {PromiseInit>} initReadyP : signal main thread initialization is done.
     * @return {bool}                    : true if success, false otherwise
     */
    bool guiEngine(PromiseInit* pInitReadyP = nullptr);

    /** Renders main window */
    void mainWindowRender();
    /** Draw on canvas */
    void draw();

    /** Callback for size */
    static void size_callback(GLFWwindow* window, int width, int height);

    /** Separate thread to run GUI engine */
    //Os::Thread threadM;
    /** Instance of os main window */
    GLFWwindow* pOsWindowM;
    /** Main window widget */
    IWindow* pMainWidgetWindowM;
    /** Flag used to stop the engine */
    bool stopEngineM;
    /** Synchronize operations before a new frame starts */
    Mutex syncBeforeFrameStartsM;
    
    /** Result value of engine thread execution */
    std::future<bool> engineResultM;
    /** Collection of created fonts */
    Bind::Rebol2::FontsMap fontsM;
    /** Flag indicating new font has been added */
    bool newFontAddedM;
    /** Flag indicating if GUI engine runs in background thread */
    bool isRuningInBkgThreadM;
    /** One instance for one main window  */
    static owner<OpenGL*> pEngineinstanceM;
    /** Flag indicating if engine is started */
    bool engineStartedM;
};

} // namespace GUI