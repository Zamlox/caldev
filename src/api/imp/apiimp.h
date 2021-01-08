/**
 * Author: 		Iosif Haidu
 * Description: API implemnetation 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_APIIMP_H__
#define __API_APIIMP_H__

#include "modules/gui/igui.h"
#include <memory>
#include <gsl/string_span.h>

namespace Api
{
    
using namespace gsl;

// TODO: Create a common place for error codes
constexpr int ERROR_API_NOT_INITIALIZED{-2};

/**
 * GUI type
 */
enum class GuiType {
    GUI_OPENGL2,
    GUI_DIRECTX
};

/**
 * Type of thread to execute gui engine
 */
enum class GuiEngineExecutionType {
    MAIN_THREAD,
    BKG_THREAD
};

/**
 * API implementation
 */
class ApiImp
{
public:
    /**
     * Initialize GUI engine
     * 
     * @param  {GuiType} guiTypeP   : type of GUI
     * @return {int}                : 0 if success, -1 if fail
     */
    int guiEngineInit(GuiType guiTypeP);

    /**
     * Start GUI engine within main or background thread.
     * 
     * @param  {GuiEngineExecutionType} threadTypeP : type of thread
     * @return {int}                                : 0 if success, -1 otherwise
     */
    int guiEngineStart(GuiEngineExecutionType threadTypeP = GuiEngineExecutionType::BKG_THREAD);
    
    /**
     * Stop GUI engine.
     * 
     * @return {int}  : 0 if success, -1 if fail
     */
    int guiEngineStop();

    /**
     * Create main window. Only one main window allowed per application.
     * 
     * @param  {czstring} titleP    : window title
     * @param  {int} xP             : X coordinate of top-left corner of window content
     * @param  {int} yP             : y coordinate of top-left corner of window content
     * @param  {int} widthP         : window width
     * @param  {int} heightP        : window height
     * @param  {int} bgColorP       : background color
     * @param  {bool} visibleP      : window visibility
     * @return {int}                : 0 if succeeded, -1 if window creation failes or -2
     *                                  if GUI not initialized by calling initGUI
     */
    int  createMainWindow(
        czstring<> titleP, 
        int xP, int yP, 
        int widthP, 
        int heightP, 
        int bgColorP, 
        int visibleP);

    /**
     * Hide main window.
     */
    void hideMainWindow();

    /**
     * Show main window if created.
     */
    void showMainWindow();

private:
    /**
     * Engine instance.
     */
    std::unique_ptr<GUI::IGui> pGuiEngineM;
};

} // namespace Api

#endif // __API_APIIMP_H__