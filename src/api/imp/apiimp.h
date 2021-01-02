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

namespace Api
{
    
// TODO: Create a common place for error codes
constexpr int ERROR_API_NOT_INITIALIZED{-2};

/**
 * GUI type
 */
using GuiType = enum {
    GUI_OPENGL2,
    GUI_DIRECTX
};

/**
 * API implementation
 */
class ApiImp
{
public:
    /**
     * Initialize GUI 
     * 
     * @param  {int} guiTypeP : type of GUI
     * @return {int}          : 0 if success, -1 if fail
     */
    int initGUI(int guiTypeP);
    
    /**
     * Stop GUI engine.
     * 
     * @return {int}  : 0 if success, -1 if fail
     */
    int stopGUI();

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
     * @return {int}           : 0 if succeeded, -1 if window creation failes or -2
     *                              if GUI not initialized by calling initGUI
     */
    int  createMainWindow(
        char const* titleP, 
        int xP, int yP, 
        int widthP, 
        int heightP, 
        int bgColorP, 
        bool visibleP = true);

private:
    /**
     * Engine instance.
     */
    std::unique_ptr<GUI::IGui> pGuiEngineM;
};

} // namespace Api

#endif // __API_APIIMP_H__