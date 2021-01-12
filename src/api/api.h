/**
 * Author: 		Iosif Haidu
 * Description: API to interface with external world
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_H__
#define __API_H__

#include "api/export.h"
#include "api/imp/apiimp.h"

// for C++ binding
constexpr int GUI_TYPE_OPENGL2  = static_cast<int>(Api::GuiType::GUI_OPENGL2);
constexpr int GUI_TYPE_DIRECTX  = static_cast<int>(Api::GuiType::GUI_DIRECTX);
constexpr int GUI_MAIN_THREAD   = static_cast<int>(Api::GuiEngineExecutionType::MAIN_THREAD);
constexpr int GUI_BKG_THREAD    = static_cast<int>(Api::GuiEngineExecutionType::BKG_THREAD);

/**
 * Initialize GUI
 * 
 * @param  {int} guiTypeP       : type of GUI
 * @param  {int} threadTypeP    : type of thread to execute GUI Engine
 * @return {int}                : SUCCESS if succeeded
 *                                  ERR_GUI_INVALID_GUI_ENGINE_TYPE if invalid GUI type value
 *                                  ERR_GUI_INVALID_THREAD_TYPE if invalid thread type value
 *                                  ERR_GUI_CANNOT_INITIALIZE if GUi Engine fail to iniitalize
 */
EXPORT int guiEngineInit(int guiTypeP, int threadTypeP);

/**
 * Start GUI engine with specified thread type.
 * 
 * @return {int}    :   SUCCESS if succeeded
 *                          ERR_GUI_EXEC_ENGINE if fail executing GUI engine thread
 *                          ERR_GUI_ENGINE_NOT_INIT if guiEngineInit() not called
 */
EXPORT int guiEngineStart();

/**
 * Stop GUI engine
 * 
 * @return {int}  : SUCCESS if succeeded
 *                      ERR_GUI_ENGINE_NOT_INIT if guiEngineInit() not called
 */
EXPORT int guiEngineStop();

/**
 * Create main window. Only one main window allowed per application.
 * 
 * @param  {char*} const   : window title
 * @param  {int} xP        : X coordinate of top-left corner of window content
 * @param  {int} yP        : y coordinate of top-left corner of window content
 * @param  {int} widthP    : window width
 * @param  {int} heightP   : window height
 * @param  {int} bgColorP  : background color
 * @param  {bool} visibleP : window visibility
 * @return {int}           : SUCCESS if succeeded
 *                              ERR_GUI_ENGINE_NOT_INIT if guiEngineInit() not called
 *                              ERR_GUI_MAIN_WINDOW_FAILED if main os window not created
 */
EXPORT int createMainWindow(
    char const* titleP, 
    int xP, 
    int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    int visibleP);

/**
 * Hide main window.
 */
EXPORT void hideMainWindow();

/**
 * Show main window if created.
 */
EXPORT void showMainWindow();

#endif // __API_H__