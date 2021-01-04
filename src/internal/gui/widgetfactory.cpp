/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgetfactory.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/window.h"
#include <string>

namespace GUI
{

IWidgetFactory* WidgetFactory::pInstanceM{nullptr};

WidgetFactory::WidgetFactory()
    : indexM{0}
{
}

IWidgetFactory& WidgetFactory::instance()
{
    if (pInstanceM == nullptr)
    {
        pInstanceM = new WidgetFactory;
    }
    assert(pInstanceM);
    return *pInstanceM;
}

owner<IWindow*> WidgetFactory::createWindow(const char* titleP, int flags, Font* pFontP)
{
    StringBuffer buffer;
    owner<IWindow*> pWindow{nullptr};
    if (indexM != MAX_ID)
    {
        buffer.appendf("%s###%d", titleP, ++indexM);
        pWindow = new Window(buffer.c_str(), flags, pFontP);
        assert(pWindow);
        pWindow->setId(indexM);
    }
    return pWindow;
}

void WidgetFactory::destroyWindow(IWindow*& pWindowP)
{
    delete pWindowP;
    pWindowP = nullptr;
}

} // namespace GUI