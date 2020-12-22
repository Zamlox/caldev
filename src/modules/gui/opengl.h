/**
 * Author: 		Iosif Haidu
 * Description: GUI engine implementation based on OpenGL 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "igui.h"
#include "thread.h"
#include "iwindow.h"
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
    /** see IGui::start() */
    bool start() override;
    /** see IGui::stop() */
    bool stop() override;
    /** see IGui::createMainWindow() */
    int  createMainWindow(char const* titleP, int xP, int yP, int widthP, int heightP, int bgColorP) override;
    /** see IGui::hideMainWindow() */
    void hideMainWindow() override;

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
    /** Main window info */
    std::unique_ptr<IWindow> pMainWidgetWindowM;
    /** Flag used to stop the engine */
    bool stopEngineM;
};

} // namespace GUI