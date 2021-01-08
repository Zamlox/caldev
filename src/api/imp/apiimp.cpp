/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/imp/apiimp.h"
#include "modules/gui/opengl.h"

namespace Api
{

ApiImp::ApiImp()
    : pGuiEngineM{nullptr}
    , guiEngineThreadTypeM{false}
{
    
}

GuiType ApiImp::convertGuiType(int valueP)
{
    switch(valueP)
    {
        case 0: return GuiType::GUI_OPENGL2;
        case 1: return GuiType::GUI_DIRECTX;
        default: return GuiType::INVALID_TYPE;
    }
}

GuiEngineExecutionType ApiImp::convertGuiEngineExecutionType(int valueP)
{
    switch(valueP)
    {
        case 0: return GuiEngineExecutionType::MAIN_THREAD;
        case 1: return GuiEngineExecutionType::BKG_THREAD;
        default: return GuiEngineExecutionType::INVALID_THREAD;
    }
}

int ApiImp::guiEngineInit(GuiType guiTypeP, GuiEngineExecutionType threadTypeP)
{
    switch(guiTypeP)
    {
        case GuiType::GUI_OPENGL2:
            pGuiEngineM.reset(new GUI::OpenGL);
            break;
        case GuiType::GUI_DIRECTX:
            break;
        default:
            fprintf(stderr, "Invalid GUI engine type !\n");
            return -1;
    }
    if (threadTypeP == GuiEngineExecutionType::INVALID_THREAD)
    {
        fprintf(stderr, "Invalid thread type !\n");
        return -2;
    }
    guiEngineThreadTypeM = (threadTypeP == GuiEngineExecutionType::BKG_THREAD) ? true : false;
    if (!pGuiEngineM->init(guiEngineThreadTypeM))
    {
        fprintf(stderr, "Cannot initialize GUI engine !\n");
        return -1;
    }
    return 0;
}

int ApiImp::guiEngineStart()
{
    if (pGuiEngineM.get() && !pGuiEngineM->startOnThread())
    {
        fprintf(stderr, "Cannot start GUI engine in background thread !\n");
        return -1;
    }
    else if (pGuiEngineM.get() && !pGuiEngineM->startOnMainThread())
    {
        fprintf(stderr, "Cannot start GUI engine in main thread !\n");
        return -1;
    }
    else if (pGuiEngineM.get() == nullptr)
    {
        fprintf(stderr, "GUI engine instance not inititalized. Call guiEngineInit() !\n");
        return -2;
    }
    
    return 0;
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
