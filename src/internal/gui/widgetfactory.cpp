/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/imgui/common.h"
#include "internal/gui/widgetfactory.h"
#include "internal/gui/widgets/area.h"
#include "internal/gui/widgets/button.h"
#include "internal/gui/widgets/checkbox.h"
#include "internal/gui/widgets/field.h"
#include "internal/gui/widgets/label.h"
#include "internal/gui/widgets/radio.h"
#include "internal/gui/window.h"
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

owner<IWindow*> WidgetFactory::createWindow(czstring<> titleP, int flags, Font* pFontP, Id parentIdP)
{
    StringBuffer buffer;
    owner<IWindow*> pWindow{nullptr};
    if (indexM != MAX_ID)
    {
        buffer.appendf("%s###%d", titleP, ++indexM);
        pWindow = new Window(buffer.c_str(), flags, pFontP, indexM, parentIdP);
        assert(pWindow);
        //pWindow->setId(indexM);
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
IWidget* WidgetFactory::createArea(const char* textP, ImFont* pFontP, int styleP)
{
    return setupWidget(new Widget::Area(textP, pFontP, styleP));
}

IWidget* WidgetFactory::createField(const char* textP, ImFont* pFontP, int styleP, const char* pHintP)
{
    return (pHintP) ? setupWidget(new Widget::Field(textP, pFontP, styleP, pHintP))
                    : setupWidget(new Widget::Field(textP, pFontP, styleP));
}

IWidget* WidgetFactory::createButton(const char* textP, ImFont* pFontP)
{
    return setupWidget(new Widget::Button(textP, pFontP));
}

IWidget* WidgetFactory::createCheckbox(const char* textP, ImFont* pFontP, ::Color* pCheckMarkColorP)
{
    Color markColor;
    Color* pMarkColor{nullptr};
    if (pCheckMarkColorP)
    {
        markColor = GUI::Base<IWidget>::NormalizeColor(*pCheckMarkColorP);
        pMarkColor = &markColor;
    }
    return setupWidget(new Widget::Checkbox(
        textP, 
        pFontP, 
        pMarkColor));
}

IWidget* WidgetFactory::createRadioButton(const char* textP, ImFont* pFontP, ::Color* pCheckMarkColorP, int groupIdP, int selectedP)
{
    Color markColor;
    Color* pMarkColor{nullptr};
    if (pCheckMarkColorP)
    {
        markColor = GUI::Base<IWidget>::NormalizeColor(*pCheckMarkColorP);
        pMarkColor = &markColor;
    }
    return setupWidget(new Widget::RadioButton(
        textP, 
        pFontP, 
        pMarkColor,
        groupIdP,
        selectedP));
}

IWidget* WidgetFactory::setupWidget(IWidget* pWidgetP)
{
    if (pWidgetP != nullptr)
    {
        pWidgetP->setId(++indexM);
    }
    return pWidgetP;
}

} // namespace GUI