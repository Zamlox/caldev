/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/imp/apiimp.h"
#include "modules/gui/opengl.h"
#include "internal/tools/logic.h"

namespace Api
{

using namespace Logic;

ApiImp::ApiImp()
    : pGuiEngineM{nullptr}
    , guiEngineBkgThreadM{false}
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
    guiEngineBkgThreadM = (threadTypeP == GuiEngineExecutionType::BKG_THREAD) ? true : false;
    return check(0).error_if_true(
        all (threadTypeP == GuiEngineExecutionType::INVALID_THREAD),
        -2, "Invalid thread type !\n"
    ).error_if_true(
        all (!pGuiEngineM->init(guiEngineBkgThreadM)),
        -1, "Cannot initialize GUI engine !\n"
    ).result();
}

int ApiImp::guiEngineStart()
{
    return check(0).error_if_true(
        all(pGuiEngineM.get(), !pGuiEngineM->start()),
        -1, "Error executing GUI engine thread !\n"
    ).error_if_true(
        all(pGuiEngineM.get() == nullptr),
        -2, "GUI engine instance not inititalized. Call guiEngineInit() before calling guiEngineStart() !\n"
    ).result();
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
