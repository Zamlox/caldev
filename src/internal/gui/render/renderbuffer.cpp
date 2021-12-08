/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/render/renderbuffer.h"
#include "internal/gui/imgui/common.h"

namespace GUI {

RenderBuffer::RenderBuffer(bool hasSharedElemsP)
    : widgetsM{hasSharedElemsP}
{
}

void RenderBuffer::add(const Widget::CommandElem& rCommandP, bool cloneWidgetP)
{
    Widget::Storage::Index itElem;
    if (rCommandP.getGuiType() == Widget::GuiElemType::Widget)
    {
        IWidget* pWidget = (cloneWidgetP) ? rCommandP.getWidget()->clone() : rCommandP.getWidget();
        itElem = widgetsM.add(pWidget, rCommandP.getParentId());
    }
    else
    {
        IWindow* pWindow =  (cloneWidgetP) ? rCommandP.getWindow()->clone() : rCommandP.getWindow();
        itElem = widgetsM.add(pWindow, rCommandP.getParentId());            
    }
    if (rCommandP.getParentId() == PARENT_NONE)
    {
        rootWidgetsM.push_back(itElem);
    }
}

void RenderBuffer::remove(const Widget::CommandElem& rCommandP)
{

}

void RenderBuffer::update(const Widget::CommandElem& rCommandP)
{
    Widget::Storage::Index itElem;
    bool isWidget{rCommandP.getGuiType() == Widget::GuiElemType::Widget};
    if (isWidget)
    {
        IWidget* pWidgetStored{widgetsM.getElement(rCommandP.getWidget()->getId())};
        if (pWidgetStored)
        {
            widgetsM.remove(pWidgetStored);
        }
        IWidget* pWidget = rCommandP.getWidget();
        itElem = widgetsM.add(pWidget, rCommandP.getParentId());
    }
    else
    {
        IWindow* pWindowStored{static_cast<IWindow*>(widgetsM.getElement(rCommandP.getWindow()->getId()))};
        if (pWindowStored)
        {
            widgetsM.remove(pWindowStored);
        }
        IWindow* pWindow = rCommandP.getWindow();
        itElem = widgetsM.add(pWindow, rCommandP.getParentId());
    }

    // remove from root widgets and then check if we need to add it again
    std::remove_if(rootWidgetsM.begin(), rootWidgetsM.end(), [&](Widget::StorageElem::StorageIndex& rItP){
        if (isWidget && (rItP->widget.pWidget->getId() == rCommandP.getWidget()->getId()))
        {
            return true;
        }
        else if (!isWidget && (rItP->widget.pWindow->getId() == rCommandP.getWindow()->getId()))
        {
            return true;
        }
        return false;
    });
    if (rCommandP.getParentId() == PARENT_NONE)
    {
        rootWidgetsM.push_back(itElem);
    }
}

RenderBuffer::RootWidgets const& RenderBuffer::getRenderable() const
{
    return rootWidgetsM;
}

} // namespace GUI