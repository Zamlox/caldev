/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/imgui/common.h"
#include "internal/gui/widgetfactory.h"
#include "internal/gui/widgets/area.h"
#include "internal/gui/widgets/button.h"
#include "internal/gui/widgets/checkbox.h"
#include "internal/gui/widgets/combo.h"
#include "internal/gui/widgets/field.h"
#include "internal/gui/widgets/image.h"
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

owner<IWindow*> WidgetFactory::createWindow(czstring<> titleP, int flags, Font* pFontP, Id parentIdP, bool isCloningP)
{
    StringBuffer buffer;
    owner<IWindow*> pWindow{nullptr};
    if (!isCloningP)
    {
        if (indexM != MAX_ID)
        {
            buffer.appendf("%s###%d", titleP, ++indexM);
            pWindow = new Window(buffer.c_str(), flags, pFontP, indexM, parentIdP);
            assert(pWindow);
            //pWindow->setId(indexM);
        }
    }
    else
    {
        buffer.appendf(" ");
        pWindow = new Window(buffer.c_str(), flags, pFontP, indexM, parentIdP);
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

IWidget* WidgetFactory::createLabel(const char* textP, ImFont* pFontP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Label(textP, pFontP)
                        : setupWidget(new Widget::Label(textP, pFontP));
}
IWidget* WidgetFactory::createArea(const char* textP, ImFont* pFontP, int styleP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Area(textP, pFontP, styleP)
                        : setupWidget(new Widget::Area(textP, pFontP, styleP));
}

IWidget* WidgetFactory::createField(const char* textP, ImFont* pFontP, int styleP, const char* pHintP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Field(textP, pFontP, styleP, nullptr)
                        : (pHintP) ? setupWidget(new Widget::Field(textP, pFontP, styleP, pHintP))
                                   : setupWidget(new Widget::Field(textP, pFontP, styleP));
}

IWidget* WidgetFactory::createButton(const char* textP, ImFont* pFontP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Button(textP, pFontP)
                        : setupWidget(new Widget::Button(textP, pFontP));
}

IWidget* WidgetFactory::createCheckbox(const char* textP, ImFont* pFontP, ::Color* pCheckMarkColorP, bool isCloningP)
{
    Color markColor;
    Color* pMarkColor{nullptr};
    if (pCheckMarkColorP)
    {
        markColor = GUI::Base<IWidget>::NormalizeColor(*pCheckMarkColorP);
        pMarkColor = &markColor;
    }
    return (isCloningP) ? new Widget::Checkbox(textP, pFontP, pMarkColor)
                        : setupWidget(new Widget::Checkbox(textP, pFontP, pMarkColor));
}

IWidget* WidgetFactory::createRadioButton(const char* textP, ImFont* pFontP, ::Color* pCheckMarkColorP, int groupIdP, int selectedP, bool isCloningP)
{
    Color markColor;
    Color* pMarkColor{nullptr};
    if (pCheckMarkColorP)
    {
        markColor = GUI::Base<IWidget>::NormalizeColor(*pCheckMarkColorP);
        pMarkColor = &markColor;
    }
    return (isCloningP) ? new Widget::RadioButton(textP, pFontP, pMarkColor, groupIdP, selectedP)
                        : setupWidget(new Widget::RadioButton(textP, pFontP, pMarkColor, groupIdP, selectedP));
}

IWidget* WidgetFactory::createImage(Api::GuiType guiTypeP, unsigned char* pDataP, int widthP, int heightP, int nChannelsP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Image(guiTypeP, pDataP, widthP, heightP, nChannelsP)
                        : setupWidget(new Widget::Image(guiTypeP, pDataP, widthP, heightP, nChannelsP));
}

IWidget* WidgetFactory::createComboButton(const char** pItems, int countP, int selectedP, ImFont* pFontP, bool isCloningP)
{
    return (isCloningP) ? new Widget::Combo(pItems, countP, selectedP, pFontP)
                        : setupWidget(new Widget::Combo(pItems, countP, selectedP, pFontP));
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