/**
 * 
 * Author: 		Iosif Haidu
 * Description: Base class for widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/imgui/common.h"
#include "internal/gui/storage/widgetstorage.h"
#include "extern/imgui/imgui_internal.h"
#include "extern/rebsdev/src/glue/face/rebtypes.h"
#include <mutex>

extern "C" Para gDefaultPara;

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
        , frColorM{0.0, 0.0, 0.0, 0.0}
        , alignM{0.5, 0.5}
        , isWrapM{false}
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
     * @param  {bool} valueP : true for visible, false otherwise
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

    /** see IWidget::addChild() */
    void addChild(IWidget& rWidgetP) override
    {
        widgetsM.add(&rWidgetP);
    }

    /** see IWidget::update() */
    void update(GlueFace const& rFaceP) override
    {
        syncRenderM.lock();
        
        // color
        if (!rFaceP.color.none)
        {
            bgColorM.x = rFaceP.color.value.a / 255.0;
            bgColorM.y = rFaceP.color.value.b / 255.0;
            bgColorM.z = rFaceP.color.value.c / 255.0;
            bgColorM.w = 1;
        }
        // size
        if (!rFaceP.size.none)
        {
            widthM  = rFaceP.size.value.x;
            heightM = rFaceP.size.value.y;
        }
        // offset
        if (!rFaceP.offset.none)
        {
            xM = rFaceP.offset.value.x;
            yM = rFaceP.offset.value.y;
        }
        // font
        if (!rFaceP.font.none)
        {
            // color
            if (!rFaceP.font.value.color.none)
            {
                const ::Color& color{rFaceP.font.value.color.value};
                frColorM.x = color.a / 255.0;
                frColorM.y = color.b / 255.0;
                frColorM.z = color.c / 255.0;
                frColorM.w = 1;
            }
            // horizontal align
            if (!rFaceP.font.value.align.none)
            {
                const int& align{rFaceP.font.value.align.value};
                switch(align)
                {
                case FontAlign::FONT_LEFT:
                    alignM.x = 0.0;
                    break;
                case FontAlign::FONT_CENTER:
                    alignM.x = 0.5;
                    break;
                case FontAlign::FONT_RIGHT:
                    alignM.x = 1.0;
                    break;
                }
            }
            // vertical align
            if (!rFaceP.font.value.valign.none)
            {
                const int& valign{rFaceP.font.value.valign.value};
                switch(valign)
                {
                case FontAlign::FONT_TOP:
                    alignM.y = 0.0;
                    break;
                case FontAlign::FONT_MIDDLE:
                    alignM.y = 0.5;
                    break;
                case FontAlign::FONT_BOTTOM:
                    alignM.y = 1.0;
                    break;
                }
            }
        }
        // para
        if (!rFaceP.para.none)
        {
            // wrap
            if (!rFaceP.para.value.wrap.none)
            {
                isWrapM = (rFaceP.para.value.wrap.value != 0) ? true : false;
            }
            else
            {
                isWrapM = (gDefaultPara.wrap.value != 0) ? true : false;
            }
        }

        syncRenderM.unlock();
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
    /* Foreground color */
    Color frColorM;
    /** Alignment */
    Align alignM;
    /** Wrap flag */
    bool isWrapM;
    /** Mutex to synchronize render related operations */
    std::mutex syncRenderM;
    /** Storage for child widgets */
    Storage::WidgetStorage widgetsM;
};

} // namespace GUI
