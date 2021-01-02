/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/api.h"
#include "api/imp/apiimp.h"
#include <assert.h>
#include <memory>

std::unique_ptr<Api::ApiImp> pAPI{new Api::ApiImp};

EXPORT int initGUI (int guiTypeP)
{
    assert(pAPI != nullptr);
    return pAPI->initGUI(guiTypeP);
}

EXPORT int stopGUI()
{
    assert(pAPI != nullptr);
    return pAPI->stopGUI();
}

EXPORT int createMainWindow(
    char const* titleP, 
    int xP, 
    int yP, 
    int widthP, 
    int heightP, 
    int bgColorP, 
    bool visibleP)
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
