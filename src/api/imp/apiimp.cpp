/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/imp/apiimp.h"
#include "modules/gui/opengl.h"
#include "internal/tools/logic.h"
#include "internal/errors/errors.h"

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
    bool isGuiTypeInvalid{false};
    switch(guiTypeP)
    {
        case GuiType::GUI_OPENGL2:
            pGuiEngineM.reset(new GUI::OpenGL);
            break;
        case GuiType::GUI_DIRECTX:
            break;
        default:
            isGuiTypeInvalid = true;
            break;
    }
    guiEngineBkgThreadM = (threadTypeP == GuiEngineExecutionType::BKG_THREAD) ? true : false;

    return check(SUCCESS).error_if_true(
        all (isGuiTypeInvalid),
        ERR_GUI_INVALID_GUI_ENGINE_TYPE, MSG_ERR_GUI_INVALID_GUI_ENGINE_TYPE
    ).error_if_true(
        all (threadTypeP == GuiEngineExecutionType::INVALID_THREAD),
        ERR_GUI_INVALID_THREAD_TYPE, MSG_ERR_GUI_INVALID_THREAD_TYPE
    ).execute_if_no_error([=](){
        check::ErrResult error{check::make_error(ERR_GUI_CANNOT_INITIALIZE, MSG_ERR_GUI_CANNOT_INITIALIZE)};
        return pGuiEngineM->init(guiEngineBkgThreadM) ? check::success() : error;
    }).result();
}

int ApiImp::guiEngineStart()
{
    return check(SUCCESS).error_if_true(
        all(pGuiEngineM.get(), guiEngineBkgThreadM, !pGuiEngineM->startOnThread()),
        ERR_GUI_EXEC_ENGINE_BKG_THREAD, MSG_ERR_GUI_EXEC_ENGINE_BKG_THREAD
    ).error_if_true(
        all(pGuiEngineM.get(), !guiEngineBkgThreadM, !pGuiEngineM->startOnMainThread()),
        ERR_GUI_EXEC_ENGINE_MAIN_THREAD, MSG_ERR_GUI_EXEC_ENGINE_MAIN_THREAD
    ).error_if_true(
        all(pGuiEngineM.get() == nullptr),
        ERR_GUI_ENGINE_NOT_INIT, MSG_ERR_GUI_ENGINE_NOT_INIT
    ).result();
}

int ApiImp::guiEngineStop()
{
    return check(SUCCESS).error_if_true(
        all (pGuiEngineM.get() == nullptr),
        ERR_GUI_ENGINE_NOT_INIT, MSG_ERR_GUI_ENGINE_NOT_INIT
    ).execute_if_no_error([=](){
        pGuiEngineM->stop();
        pGuiEngineM.reset(nullptr); 
        return check::success();
    }).result();
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
    return ERR_GUI_ENGINE_NOT_INIT;
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
