/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/imp/apiimp.h"
#include "modules/gui/opengl.h"

namespace Api
{

int ApiImp::initGUI(int guiTypeP)
{
    switch(guiTypeP)
    {
        case GUI_OPENGL2:
            pGuiEngineM.reset(new GUI::OpenGL);
#ifndef OS_MACOS
            if(!pGuiEngineM->startOnThread())
            {
                fprintf(stderr, "Cannot start OpenGL engine !\n");
                exit(1);
            }
#endif
            return 0;
        case GUI_DIRECTX:
            return 0;
    }
    return -1;
}

int ApiImp::stopGUI()
{
    if (pGuiEngineM.get())
    {
        pGuiEngineM->stop();
        pGuiEngineM.reset(nullptr);
        return 0;
    }
    return -1;
}

int  ApiImp::createMainWindow(
    char const* titleP, 
    int xP, int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    bool visibleP)
{
    if (pGuiEngineM.get())
    {
        return pGuiEngineM->createMainWindow(
            titleP,
            xP, yP,
            widthP,
            heightP,
            bgColorP,
            visibleP);
    }
    return ERROR_API_NOT_INITIALIZED;
}


} // namespace Api
