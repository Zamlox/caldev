/**
 * Author: 		Iosif Haidu
 * Description: Render buffering
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/render/renderbuffer.h"

namespace GUI {

class RenderBuffering
{
public:
    using BufferType = enum {
        ACTIVE_BUFFER,
        INACTIVE_BUFFER
    };

    RenderBuffering();
    ~RenderBuffering();
    /**
     * Swap buffers.
     */
    void swapBuffers();
    /**
     * Call this function after swapBuffers().
     * Update contetn of non active buffer to be same as the active buffer.
     * Call it in post render phase.
     */
    void normalizeBuffers();

    /**
     * Add widget to non active buffer.
     * 
     * @param  {Widget::CommandElem} rCommandP : command for adding widget
     */
    void add(const Widget::CommandElem& rCommandP);
    /**
     * Remove widget from non active buffer.
     * 
     * @param  {Widget::CommandElem} rCommandP : commnand for removing widget
     */
    void remove(const Widget::CommandElem& rCommandP);
    /**
     * Update widget from non acvtive buffer.
     * 
     * @param  {Widget::CommandElem} rCommandP : command for updating widget
     */
    void update(const Widget::CommandElem& rCommandP);

    /**
     * Call this function after swapBuffers().
     * Get content of active buffer.
     * 
     * @return {RenderBuffer::RootWidgets}  : list of widgets 
     */
    RenderBuffer::RootWidgets const& getContentActiveBuffer() const;

    IWidget* getWidget(Id idP, BufferType bufferTypeP);
    IWindow* getWindow(Id idP, BufferType bufferTypeP);
    Widget::Storage::Container const& getElements();

private:
    RenderBuffer buffer1M;
    RenderBuffer buffer2M;
    RenderBuffer* pBufferActiveM;
    RenderBuffer* pBufferNonActiveM;
    using ListCommands = std::list<Widget::CommandElem>;
    ListCommands commandsM;
};

inline IWidget* RenderBuffering::getWidget(Id idP, BufferType bufferTypeP)
{
    return (bufferTypeP == ACTIVE_BUFFER) ? pBufferActiveM->getWidget(idP) 
                                          : pBufferNonActiveM->getWidget(idP);
}

inline IWindow* RenderBuffering::getWindow(Id idP, BufferType bufferTypeP)
{
    return (bufferTypeP == ACTIVE_BUFFER) ? pBufferActiveM->getWindow(idP)
                                          : pBufferNonActiveM->getWindow(idP);
}

inline Widget::Storage::Container const& RenderBuffering::getElements()
{
    return pBufferActiveM->getElements();
}

} // namespace GUI
