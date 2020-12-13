/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "opengl.h"

namespace GUI
{

OpenGL::OpenGL()
    : threadM{"GuiEngine", &OpenGL::initGuiEngine, &OpenGL::guiEngine, this}
{
    
}

bool OpenGL::start()
{
    return threadM.start();
}

bool OpenGL::stop()
{
    return true;
}

void* OpenGL::initGuiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);
    return nullptr;
}

void* OpenGL::guiEngine(void* pParamP)
{
    OpenGL* pOpenGL = static_cast<OpenGL*>(pParamP);
    return nullptr;
}

} // namespace GUI