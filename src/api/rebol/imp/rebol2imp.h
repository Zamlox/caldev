/**
 * Author: 		Iosif Haidu
 * Description: Implementation for Rebol2 API 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_REBOL2IMP_H__
#define __API_REBOL2IMP_H__

#include "modules/gui/igui.h"

namespace Api
{
    
/**
 * GUI type
 * Same values must be used from Rebol when initializing GUI
 */
using GuiType = enum {
    GUI_OPENGL2,
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
    /**
     * Stop GUI engine.
     * @return {int}  : 0 if success, -1 if fail
     */
    int stopGUI();

private:
    /**
     * Engine instance.
     */
    std::unique_ptr<GUI::IGui> pGuiEngineM;
};

} // namespace Rebol2API

#endif // __API_REBOL2IMP_H__