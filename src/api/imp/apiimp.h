/**
 * Author: 		Iosif Haidu
 * Description: API implemnetation 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_APIIMP_H__
#define __API_APIIMP_H__

#include "modules/gui/igui.h"
#include "api/imp/apiconst.h"
#include <memory>
#include <gsl/string_span.h>

namespace Api
{
    
using namespace gsl;

/**
 * API implementation
 */
class ApiImp
{
public:
    ApiImp();

    /**
     * Converts an int value to a GuiType value
     * 
     * @param  {int} valueP : value to be converted
     * @return {GuiType}    : result of conversion
     */
    static GuiType convertGuiType(int valueP);

    
    /**
     * Converts an int value to a GuiEngineExecutionType value
     * 
     * @param  {int} valueP              : value to be converted
     * @return {GuiEngineExecutionType}  : result of conversion
     */
    static GuiEngineExecutionType convertGuiEngineExecutionType(int valueP);

    /**
     * Initialize GUI engine
     * 
     * @param  {GuiType} guiTypeP                   : type of GUI
     * @param  {GuiEngineExecutionType} threadTypeP : type of thread to run engine
     * @return {int}                                : 0 if success, -1 if fail
     */
    int guiEngineInit(GuiType guiTypeP, GuiEngineExecutionType threadTypeP = GuiEngineExecutionType::BKG_THREAD);

    /**
     * Start GUI engine within main or background thread.
     * 
     * @return {int}    :   0 if success
     *                      -1 if GUI engine cannot run in thread
     *                      -2 if guiEngineInit() was not called before
     */
    int guiEngineStart();
    
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
    /** Type of thread for GUI engine */
    bool guiEngineBkgThreadM;
};

} // namespace Api

#endif // __API_APIIMP_H__