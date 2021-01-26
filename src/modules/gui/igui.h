/**
 * Author: 		Iosif Haidu
 * Description: GUI engines must derive from this interface 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IGUI_H__
#define __GUI_IGUI_H__

#include <gsl/string_span.h>

namespace GUI
{

using namespace gsl;

/**
 * Interface for GUI engines
 */
class IGui
{
public:
    virtual ~IGui() = default;
    /**
     * Initialize GUI engine. By default it will be initialized in a background thread.
     * Call this method before calling any of startOnThread()/startOnMainThread().
     * 
     * @param  {bool} bkgThreadP : true if must be initialized in a background thread,
     *                              false if must be initialized in main thread
     * @return {bool}            : true if successful, false otherwise
     */
    virtual bool init(bool bkgThreadP = true) = 0;
    
    /**
     * Starts GUI engine in a different thread then main thread
     * @return {bool}  :  true if succeeded, false otherwise
     */
    virtual bool startOnThread() = 0;

    /**
     * Starts GUI engine in main thread.
     * 
     * GUI widgets must be created after calling 
     * @return {bool}                       : true if succeeded, false otherwise
     */
    virtual bool startOnMainThread() = 0;

    /**
     * Stops GUI engine
     * @return {bool}  : true if succeeded, false otherwise
     */
    virtual bool stop() = 0;
    /**
     * Create main window.
     * @param  {czstring}       : title of main window
     * @param  {int} xP         : top-left x position
     * @param  {int} yP         : top-left y position
     * @param  {int} widthP     : width of window
     * @param  {int} heightP    : height of window
     * @param  {int} bgColorP   : background color
     * @param  {bool} visibleP  : true if window visible, false otherwise
     * @return {int}            : window id if succeeded, INVALID_WIDGET_ID otherwise
     */
    virtual int createMainWindow(
        czstring<> titleP, 
        int xP, int yP, 
        int widthP, int heightP, 
        int bgColorP,
        bool visibleP = true) = 0;
    /**
     * Hide main window
     */
    virtual void hideMainWindow() = 0;
    /**
     * Show main window
     */
    virtual void showMainWindow() = 0;
};

} // namespace GUI

#endif // __GUI_IGUI_H__