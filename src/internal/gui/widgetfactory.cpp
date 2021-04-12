/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgetfactory.h"
#include "internal/gui/imgui/common.h"
#include "internal/gui/window.h"
#include "internal/gui/widgets/label.h"
#include <string>

namespace GUI
{

WidgetFactory* WidgetFactory::pInstanceM{nullptr};

WidgetFactory::WidgetFactory()
    : indexM{0}
{
}

WidgetFactory& WidgetFactory::instance()
{
    if (pInstanceM == nullptr)
    {
        pInstanceM = new WidgetFactory;
    }
    assert(pInstanceM);
    return *pInstanceM;
}

owner<IWindow*> WidgetFactory::createWindow(czstring<> titleP, int flags, Font* pFontP)
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

void WidgetFactory::destroyWindow(owner<IWindow*>& pWindowP)
{
    delete pWindowP;
    pWindowP = nullptr;
}

void WidgetFactory::destroyWidget(owner<IWidget*>& pWidgetP)
{
    delete pWidgetP;
    pWidgetP = nullptr;
}
IWidget* WidgetFactory::createLabel(const char* textP, ImFont* pFontP)
{
    return setupWidget(new Widget::Label(textP, pFontP));
}
IWidget* WidgetFactory::setupWidget(IWidget* pWidgetP)
{
    if (pWidgetP != nullptr)
    {
        pWidgetP->setId(++indexM);
    }
    return pWidgetP;}

} // namespace GUI