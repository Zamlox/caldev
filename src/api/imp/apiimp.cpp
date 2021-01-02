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
        return 0;
    }
    return -1;
}

} // namespace Api