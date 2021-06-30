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

}

RenderBuffer::RootWidgets const& RenderBuffer::getRenderable() const
{
    return rootWidgetsM;
}

} // namespace GUI