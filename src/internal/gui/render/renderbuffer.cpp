/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/render/renderbuffer.h"
#include "internal/gui/imgui/common.h"

namespace GUI {

void RenderBuffer::add(const Widget::CommandElem& rCommandP)
{
    Widget::Storage::Index itElem;
    if (rCommandP.getGuiType() == Widget::GuiElemType::Widget)
        itElem = widgetsM.add(rCommandP.getWidget(), rCommandP.getParentId());
    else
        itElem = widgetsM.add(rCommandP.getWindow(), rCommandP.getParentId());            
    if (rCommandP.getParentId() == PARENT_NONE)
    {
        rootWidgetsM.push_back(itElem);
    }
}

void RenderBuffer::remove()
{

}

void RenderBuffer::update()
{

}

RenderBuffer::RootWidgets const& RenderBuffer::getRenderable() const
{
    return rootWidgetsM;
}

RenderBuffer& RenderBuffer::operator=(const RenderBuffer& rOpP)
{
    return *this;
}

} // namespace GUI