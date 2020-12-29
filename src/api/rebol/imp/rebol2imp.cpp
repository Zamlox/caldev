/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/rebol/imp/rebol2imp.h"
#include "modules/gui/opengl.h"

namespace Api
{

int Rebol2Imp::initGUI(int guiTypeP)
{
    switch(guiTypeP)
    {
        case GUI_OPENGL2:
            pGuiEngineM.reset(new GUI::OpenGL);
#ifndef OS_MACOS
            if(!pGuiEngineM->startOnThread())
            {
                printf("Cannot start OpenGL engine !");
                exit(1);
            }
#endif
            return 0;
        case GUI_DIRECTX:
            return 0;

    }
    return -1;
}

int Rebol2Imp::stopGUI()
{
    if (pGuiEngineM.get())
    {
        pGuiEngineM->stop();
        return 0;
    }
    return -1;
}

} // namespace Api