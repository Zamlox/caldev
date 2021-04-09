/**
 * Author: 		Iosif Haidu
 * Description: Interface for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/imgui/common.h"
#include "internal/gui/irender.h"
#include "extern/rebsdev/src/glue/face/face.h"

namespace GUI
{

/** Minimum size on x */
constexpr int MIN_SIZE_X{100};
/** Minimum size on y */
constexpr int MIN_SIZE_Y{100};

/**
 * Widget interface
 */
class IWidget : public IRender
{
public:
    virtual ~IWidget() = default;
    
    /**
     * Get id of widget.
     * 
     * @return {Id}  : widget id
     */
    virtual Id getId() const = 0;

    /**
     * Set widget it.
     * 
     * @param  {Id} idP : widget id
     */
    virtual void setId(Id idP) = 0;

    /**
     * Add child widgets.
     * 
     * @param  {IWidget&} pWidgetP : child widget to add
     */
    virtual void addChild(IWidget& rWidgetP) = 0;

    /**
     *  Update widget.
     * 
     * @param  {GlueFace} const : face to update
     */
    virtual void update(GlueFace const& rFaceP) = 0;
};

} // namespace GUI
