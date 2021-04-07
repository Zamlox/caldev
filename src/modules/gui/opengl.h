/**
 * Author: 		Iosif Haidu
 * Description: GUI engine implementation based on OpenGL 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"
#include "internal/os/thread.h"
#include "internal/os/mutex.h"
#include "internal/gui/iwindow.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/storage/widgetstorage.h"
#include "extern/rebsdev/src/glue/face/face.h"
#include "modules/gui/igui.h"
#include <GLFW/glfw3.h>
#include <functional>

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
    Font* createFont(FaceFont const& rFontP);

    /**
     * Create widget based on a face description.
     * 
     * @param  {char*} pFaceDescriptionP : face description.
     * @return {Id}                      : id of widget
     */
    Id createWidget(const char* pFaceDescriptionP);

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
    static void* guiEngine(void* pParamP);

    /** Renders main window */
    void mainWindowRender();
    /** Draw on canvas */
    void draw();

    /** Callback for size */
    static void size_callback(GLFWwindow* window, int width, int height);

    /**
     * Create widget
     * @param  {GlueFace} const : face object
     * @return {Id}             : id of widget
     */
    Id createWidget(GlueFace const& rFaceP, FaceCounters const& rCountersP);
    /**
     * Parse face description and generates face object
     * 
     * @param  {char*} faceDescriptionP : description of face
     * @param  {GlueFace} rFaceP        : face object
     * @return {bool}                   : true if succedd, false otherwise
     */
    bool parseFaceDescription(const char* faceDescriptionP, GlueFace& rFaceP, FaceCounters& rCountersP);
    /**
     * Parse face description and calls widget creation function.
     * 
     * @param  {const char*}                                 : face description
     * @param  {std::function<Id(GlueFace)>} widgetCreatorP  : widget creation function
     * @return {Id}                                          : widget id
     */
    Id widgetStub(char const* pFaceDescriptionP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP);
    /**
     * Calls widget creation function. 
     * 
     * @param  {GlueFace} const                             : face object
     * @param  {std::function<Id(GlueFace)>} widgetCreatorP : widget creation function
     * @return {Id}                                         : widget id
     */
    Id widgetStub(GlueFace const& rFaceP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP, FaceCounters& rCountersP);
    /**
     * Create different widgets based on T.
     * 
     * @param  {GlueFace} const                          : face object
     * @param  {std::function<T*} (GlueFace const&)      : creation sfunction
     * @param  {std::function<void(void)>} beforeUpdateP : function to execute before creation
     * @return {Id}                                      : id of widget
     */
    template <typename T, typename TStorage = Storage::WidgetStorage>
    Id createStub(
        GlueFace const& rFaceP, 
        std::function<T*(GlueFace const&)> createP, 
        std::function<void(void)> beforeUpdateP = nullptr);

    /** Separate thread to run GUI engine */
    Os::Thread threadM;
    /** Instance of os main window */
    GLFWwindow* pOsWindowM;
    /** Main window widget. Contain child windows and widgets */
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
    /** Storage for widgets */
    Storage::WidgetStorage widgetsM;
};

} // namespace GUI