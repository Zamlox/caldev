/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/api.h"
#include "api/imp/apiimp.h"
#include <assert.h>
#include <memory>


std::unique_ptr<Api::ApiImp> pAPI{new Api::ApiImp};

EXPORT int guiEngineInit (int guiTypeP, int threadTypeP)
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineInit(
        Api::ApiImp::convertGuiType(guiTypeP),
        Api::ApiImp::convertGuiEngineExecutionType(threadTypeP));
}

EXPORT int guiEngineStart()
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineStart();
}

EXPORT int guiEngineStop()
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineStop();
}

EXPORT int createMainWindow(
    char const* titleP, 
    int xP, 
    int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    int visibleP)
{
    assert(pAPI != nullptr);
    return pAPI->createMainWindow(
        titleP,
        xP, yP,
        widthP,
        heightP,
        bgColorP,
        visibleP);
}

EXPORT void hideMainWindow()
{
    assert(pAPI != nullptr);
    pAPI->hideMainWindow();
}

EXPORT void showMainWindow()
{
    assert(pAPI != nullptr);
    pAPI->showMainWindow();
}

EXPORT int createWidget(Api::Face faceP)
{
    return pAPI->createWidget(faceP);
}