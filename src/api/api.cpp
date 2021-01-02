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