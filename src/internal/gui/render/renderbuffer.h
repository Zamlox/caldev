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
    void remove();
    void update();

    RootWidgets const& getRenderable() const;

    RenderBuffer& operator=(const RenderBuffer& rOpP);

private:
    /** Storage for widgets */
    Widget::Storage widgetsM;
    /** Root widgets, without parents */
    RootWidgets rootWidgetsM;
};

} // namespace GUI