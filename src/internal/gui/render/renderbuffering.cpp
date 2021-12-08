/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/render/renderbuffering.h"

namespace GUI {

RenderBuffering::RenderBuffering()
    : buffer1M{false}
    , buffer2M{false}
    , pBufferActiveM{&buffer1M}
    , pBufferNonActiveM{&buffer2M}
{
}

RenderBuffering::~RenderBuffering()
{
    pBufferActiveM = nullptr;
    pBufferNonActiveM = nullptr;
}

void RenderBuffering::swapBuffers()
{
    std::swap(pBufferActiveM, pBufferNonActiveM);
}

void RenderBuffering::normalizeBuffers()
{
    for (auto command : commandsM)
    {
        switch(command.getType())
        {
        case Widget::WidgetCommand::Create:
            pBufferNonActiveM->add(command, true);
            break;
        case Widget::WidgetCommand::Update:
            pBufferNonActiveM->update(command);
            break;
        case Widget::WidgetCommand::Remove:
            pBufferNonActiveM->remove(command);
            break;
        }
    }
    commandsM.clear();
}

void RenderBuffering::add(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->add(rCommandP);
    commandsM.push_back(rCommandP);
}

void RenderBuffering::remove(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->remove(rCommandP);
    commandsM.push_back(rCommandP);
}

void RenderBuffering::update(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->update(rCommandP);
    commandsM.push_back(rCommandP);
}

RenderBuffer::RootWidgets const& RenderBuffering::getContentActiveBuffer() const
{
    return pBufferActiveM->getRenderable();
}

} // namespace GUI
