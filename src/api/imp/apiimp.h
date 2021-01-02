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

} // namespace Api

#endif // __API_APIIMP_H__