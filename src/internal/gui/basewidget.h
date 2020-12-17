/**
 * 
 * Author: 		Iosif Haidu
 * Description: Base class for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_BASEWIDGET_H__
#define __GUI_BASEWIDGET_H__

#include "imgui/common.h"

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
    {
    }
    Base(Font* pFontP)
        : Base()
        , pFontM{pFontP}
    {
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
    void setId(Id idP)
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
};

} // namespace GUI

#endif