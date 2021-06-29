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