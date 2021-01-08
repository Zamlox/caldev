/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/imp/apiimp.h"
#include "modules/gui/opengl.h"

namespace Api
{

int ApiImp::guiEngineInit(GuiType guiTypeP)
{
    switch(guiTypeP)
    {
        case GuiType::GUI_OPENGL2:
            pGuiEngineM.reset(new GUI::OpenGL);
            return 0;
        case GuiType::GUI_DIRECTX:
            return 0;
    }
    return -1;
}

int ApiImp::guiEngineStart(GuiEngineExecutionType threadTypeP)
{
    if (pGuiEngineM.get())
    {
        bool bkgThread = (threadTypeP == GuiEngineExecutionType::BKG_THREAD) ? true : false;
        pGuiEngineM->init(bkgThread);
        if (bkgThread)
        {
            if (!pGuiEngineM->startOnThread())
            {
                fprintf(stderr, "Cannot start OpenGL engine in background thread !\n");
                exit(1);
            }
        }
        else
        {
            if (!pGuiEngineM->startOnMainThread())
            {
                fprintf(stderr, "Cannot start OpenGL engine in main thread !\n");
                exit(1);
            }
        }
    }
}

int ApiImp::guiEngineStop()
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
    czstring<> titleP, 
    int xP, int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    int visibleP)
{
    if (pGuiEngineM.get())
    {
        int res = pGuiEngineM->createMainWindow(
            titleP,
            xP, yP,
            widthP,
            heightP,
            bgColorP,
            false);
        if (visibleP != 0) 
        {   
            showMainWindow();
        }
        return res;
    }
    return ERROR_API_NOT_INITIALIZED;
}

void ApiImp::hideMainWindow()
{
    if (pGuiEngineM.get())
    {
        pGuiEngineM->hideMainWindow();
    }
}

void ApiImp::showMainWindow()
{
    if (pGuiEngineM.get())
    {
        pGuiEngineM->showMainWindow();
    }
}

} // namespace Api
