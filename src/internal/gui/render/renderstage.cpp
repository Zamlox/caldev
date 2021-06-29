/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/render/renderstage.h"

namespace GUI {

RenderStage::RenderStage()
    : buffer1M{false}
    , buffer2M{true}
    , pBufferActiveM{&buffer1M}
    , pBufferNonActiveM{&buffer2M}
{
}

RenderStage::~RenderStage()
{
    pBufferActiveM = nullptr;
    pBufferNonActiveM = nullptr;
}

void RenderStage::swapBuffers()
{
    RenderBuffer* pTemp = pBufferActiveM;
    pBufferActiveM      = pBufferNonActiveM;
    pBufferNonActiveM   = pTemp;
}

void RenderStage::normalizeBuffers()
{
    for (auto command : commandsM)
    {
        switch(command.getType())
        {
        case Widget::WidgetCommand::Create:
            pBufferNonActiveM->add(command);
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

void RenderStage::add(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->add(rCommandP);
    commandsM.push_back(rCommandP);
}

void RenderStage::remove(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->remove(rCommandP);
    commandsM.push_back(rCommandP);
}

void RenderStage::update(const Widget::CommandElem& rCommandP)
{
    pBufferNonActiveM->update(rCommandP);
    commandsM.push_back(rCommandP);
}

RenderBuffer::RootWidgets const& RenderStage::getContentActiveBuffer() const
{
    return pBufferActiveM->getRenderable();
}

} // namespace GUI
