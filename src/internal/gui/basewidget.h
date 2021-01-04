/**
 * 
 * Author: 		Iosif Haidu
 * Description: Base class for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_BASEWIDGET_H__
#define __GUI_BASEWIDGET_H__

#include "internal/gui/imgui/common.h"
#include "internal/os/mutex.h"

namespace GUI
{

/**
 * Base class for widgets
 */
template <typename T>
class Base : public T
{
public:
    Base()
        : visibleM{true}
        , idM{START_WIDGET_ID}
        , pFontM{nullptr}
        , xM{0}
        , yM{0}
        , widthM{0}
        , heightM{0}
        , bgColorM{1.0, 1.0, 1.0, 1.0}
    {
    }
    Base(Font* pFontP)
        : Base()
    {
        pFontM = pFontP;
    }
    virtual ~Base()
    {
    }
    /**
     * Set visibility.
     * @param  {bool} valueP : trur for visible, false otherwise
     */
    void setVisible(bool valueP)
    {
        visibleM = valueP;
    }
    /**
     * Get visibility value.
     * @return {bool}  : visibility value
     */
    bool isVisible() const
    {
        return visibleM;
    }
    /** see IWidget::getId() */
    Id getId() const override
    {
        return idM;
    }
    /** see IWisget::setId() */
    void setId(Id idP) override
    {
        idM = idP;
    }
    
protected:
    /** Flag indicating widget visibility */
    bool visibleM;
    /** Widget id */
    Id idM;
    /** Font */
    Font* pFontM;
    /** X position of top-left corner */
    int xM;
    /** y position of top-left corner */
    int yM;
    /** Width of window */
    int widthM;
    /** Height of window */
    int heightM;
    /** Background color */
    Color bgColorM;
    /** Mutex to synchronize render related operations */
    Os::Mutex syncRenderM;
};

} // namespace GUI

#endif