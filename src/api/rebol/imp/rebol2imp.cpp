/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "rebol2imp.h"

namespace Api
{

int Rebol2Imp::initGUI(int guiTypeP)
{
    switch(guiTypeP)
    {
        case GUI_GLFW:
            return 0;
        case GUI_DIRECTX:
            return 0;

    }
    return -1;

}

} // namespace Api