/**
 * Author: 		Iosif Haidu
 * Description: Interface for rendering widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

namespace GUI
{

/**
 * Interface to render widget
 */
class IRender
{
public:
    virtual ~IRender() = default;
    IRender() = default;

    /**
     * Begin rendering a widget.
     */
    virtual void beginRender() = 0;

    /**
     * End rendering a widget
     */
    virtual void endRender() = 0;
};

} // namespace GUI
