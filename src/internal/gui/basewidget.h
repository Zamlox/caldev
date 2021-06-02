/**
 * 
 * Author: 		Iosif Haidu
 * Description: Base class for widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/imgui/common.h"
#include "extern/imgui/imgui_internal.h"
#include "extern/rebsdev/src/glue/face/rebtypes.h"
#include <string>

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
        , parentIdM{PARENT_NONE}
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

    /** see IWidget::update() */
    void update(GlueFace const& rFaceP) override
    {
        // color
        if (!rFaceP.color.none)
        {
            bgColorM.x = rFaceP.color.value.a / 255.0;
            bgColorM.y = rFaceP.color.value.b / 255.0;
            bgColorM.z = rFaceP.color.value.c / 255.0;
            bgColorM.w = rFaceP.color.value.d / 255.0;;
            bgColorRGBM = bgColorM;
            alphaM = bgColorRGBM.w;
            bgColorRGBM.w = 1.0;
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
                frColorM.w = color.d / 255.0;;
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
    }

    void SetStyleFgColor(int colorIndexP)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        styleCacheM.push_back(style);
        style.Colors[colorIndexP] = frColorM;
        style.Alpha = 1.0;
    }
    void RestoreStyleFgColor(int colorIndexP)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[colorIndexP] = styleCacheM.back().Colors[colorIndexP];
        style.Alpha = styleCacheM.back().Alpha;
        styleCacheM.pop_back();
    }

    void SetStyleBgColor(int colorIndexP)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        styleCacheM.push_back(style);
        style.Colors[colorIndexP] = bgColorRGBM;
        style.Alpha = alphaM;
    }
    void RestoreStyleBgColor(int colorIndexP)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[colorIndexP] = styleCacheM.back().Colors[colorIndexP];
        style.Alpha = styleCacheM.back().Alpha;
        styleCacheM.pop_back();
    }

    void SetStyleFramePadding()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        styleCacheM.push_back(style);
        style.FramePadding = ImVec2(0.0f, 0.0f);
    }
    void RestoreStyleFramePadding()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.FramePadding = styleCacheM.back().FramePadding;
        styleCacheM.pop_back();
    }

protected:
    std::string& replace(std::string& s, const std::string& from, const std::string& to)
    {
        if(!from.empty())
            for(size_t pos = 0; (pos = s.find(from, pos)) != std::string::npos; pos += to.size())
                s.replace(pos, from.size(), to);
        return s;
    }

    /** Flag indicating widget visibility */
    bool visibleM;
    /** Widget id */
    Id idM;
    /** Parent widget id */
    Id parentIdM;
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
    /** Background color with alpha channel */
    Color bgColorM;
    /** Background color without alpha channel */
    Color bgColorRGBM;
    /** Alpha channel for background color bgColorRGBM */
    float alphaM;
    /* Foreground color */
    Color frColorM;
    /** Alignment */
    Align alignM;
    /** Wrap flag */
    bool isWrapM;
    /** Style used to save temporary values from current active style */
    ImVector<ImGuiStyle> styleCacheM;
};

} // namespace GUI
