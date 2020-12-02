/**
 * Author: 		Iosif Haidu
 * Description: Implementation for Rebol2 API 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */


namespace Api
{
    
    /**
     * GUI type
     * Same values must be used from Rebol when initializing GUI
     */
    using GuiType = enum {
        GUI_GLFW,
        GUI_DIRECTX
    };

    /**
     * API implementation for Rebol2
     */
    class Rebol2Imp
    {
    public:
        /**
         * Initialize GUI 
         * @param  {int} guiTypeP : type of GUI
         * @return {int}          : 0 if success, -1 if fail
         */
        int initGUI(int guiTypeP);
    };

} // namespace Rebol2API