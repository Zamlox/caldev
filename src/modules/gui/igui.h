/**
 * Author: 		Iosif Haidu
 * Description: GUI engines must derive from this interface 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

namespace GUI
{
/**
 * Interface for GUI engines
 */
class IGui
{
public:
    virtual ~IGui() = default;
    /**
     * Starts GUI engine
     * @return {bool}  :  true if succeeded, false otherwise
     */
    virtual bool start() = 0;
    /**
     * Stops GUI engine
     * @return {bool}  : true if succeeded, false otherwise
     */
    virtual bool stop() = 0;
    /**
     * Create main window.
     * @param  {char*} const    : title of main window
     * @param  {int} xP         : top-left x position
     * @param  {int} yP         : top-left y position
     * @param  {int} widthP     : width of window
     * @param  {int} heightP    : height of window
     * @param  {int} bgColorP   : background color
     * @return {bool}           : true if succeeded, false otherwise
     */
    virtual bool  createMainWindow(char const* titleP, int xP, int yP, int widthP, int heightP, int bgColorP) = 0;
    /**
     * Hide main window
     */
    virtual void hideMainWindow() = 0;
};

} // namespace GUI