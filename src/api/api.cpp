/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/api.h"
#include "api/imp/apiimp.h"
#include <assert.h>
#include <memory>

extern "C" {
#include "extern/rebsdev/src/glue/glue.h"
}

std::unique_ptr<Api::ApiImp> pAPI{new Api::ApiImp};

int init_lib()
{
    init_rebsdev();

    return 0;
}

int guiEngineInit (int guiTypeP, int threadTypeP)
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineInit(
        Api::ApiImp::convertGuiType(guiTypeP),
        Api::ApiImp::convertGuiEngineExecutionType(threadTypeP));
}

int guiEngineStart()
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineStart();
}

int guiEngineStop()
{
    assert(pAPI != nullptr);
    return pAPI->guiEngineStop();
}

int createMainWindow(
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

void hideMainWindow()
{
    assert(pAPI != nullptr);
    pAPI->hideMainWindow();
}

void showMainWindow()
{
    assert(pAPI != nullptr);
    pAPI->showMainWindow();
}

int createWidget(Api::Face faceP)
{
    return pAPI->createWidget(faceP);
}