/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_H__
#define __API_H__

#include "api/export.h"

/**
 * Initialize GUI
 * 
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
EXPORT int initGUI(int guiTypeP);

/**
 * Stop GUI engine
 * 
 * @return {int}  : 0 if succeeded
 */
EXPORT int stopGUI();

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
 * @return {int}           : 0 if succeeded, -1 otherwise
 */
EXPORT int createMainWindow(
    char const* titleP, 
    int xP, 
    int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    bool visibleP = true);

/**
 * Hide main window.
 */
EXPORT void hideMainWindow();

/**
 * Show main window if created.
 */
EXPORT void showMainWindow();

#endif // __API_H__