/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "widgetfactory.h"

namespace GUI
{

IWidgetFactory* WidgetFactory::pInstanceM{nullptr};

IWidgetFactory& WidgetFactory::instance()
{
    if (pInstanceM == nullptr)
    {
        pInstanceM = new WidgetFactory;
    }
    assert(pInstanceM);
    return *pInstanceM;
}

IWindow* WidgetFactory::createWindow(const char* titleP, int flags, Font* pFontP)
{
    return nullptr;
}

} // namespace GUI