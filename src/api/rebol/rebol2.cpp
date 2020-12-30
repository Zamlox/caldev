/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/rebol/rebol2.h"
#include "api/rebol/imp/rebol2imp.h"
#include <assert.h>
#include <memory>

std::unique_ptr<Api::Rebol2Imp> pRebol2API{new Api::Rebol2Imp};

EXPORT int initGUI (int guiTypeP)
{
    assert(pRebol2API != nullptr);
    return pRebol2API->initGUI(guiTypeP);
}

EXPORT int stopGUI()
{
    assert(pRebol2API != nullptr);
    return pRebol2API->stopGUI();
}