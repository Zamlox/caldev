/**
 * Author: 		Iosif Haidu
 * Description: Render buffer
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/widgets/queue/storage.h"
#include "internal/gui/widgets/queue/command.h"
#include <list>

namespace GUI {

class RenderBuffer
{
public:
    using RootWidgets = std::list<Widget::Storage::Index>;

    void add(const Widget::CommandElem& rCommandP);
    void remove(const Widget::CommandElem& rCommandP);
    void update(const Widget::CommandElem& rCommandP);

    RootWidgets const& getRenderable() const;

    IWidget* getWidget(Id idP);
    IWindow* getWindow(Id idP);
    Widget::Storage::Container const& getElements();

private:
    /** Storage for widgets */
    Widget::Storage widgetsM;
    /** Root widgets, without parents */
    RootWidgets rootWidgetsM;
};

inline IWidget* RenderBuffer::getWidget(Id idP)
{
    return widgetsM.getElement(idP);
}

inline IWindow* RenderBuffer::getWindow(Id idP)
{
    return static_cast<IWindow*>(widgetsM.getElement(idP));
}

inline Widget::Storage::Container const& RenderBuffer::getElements()
{
    return widgetsM.getElements();
}

} // namespace GUI