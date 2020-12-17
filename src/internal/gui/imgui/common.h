/**
 * Author: 		Iosif Haidu
 * Description: Substitute DearImGUI declarations to reduce dependency.
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IMGUI_COMMON_H__
#define __GUI_IMGUI_COMMON_H__

#include "imgui.h"

namespace GUI
{

/** Type for id */
using Id = ImGuiID;

/** Used for invalid widgets id */
constexpr Id INVALID_WIDGET_ID{-1};

/** Color type */
using Color = ImVec4;
/** Align type */
using Align = ImVec2;

/**
 * Windows creation flags
 */
using WindowsFlags = enum {
    WindowFlags_None                        = ImGuiWindowFlags_None,
    WindowFlags_NoTitleBar                  = ImGuiWindowFlags_NoTitleBar,
    WindowFlags_NoResize                    = ImGuiWindowFlags_NoResize,
    WindowFlags_NoMove                      = ImGuiWindowFlags_NoMove,
    WindowFlags_NoScrollbar                 = ImGuiWindowFlags_NoScrollbar,
    WindowFlags_NoScrollWithMouse           = ImGuiWindowFlags_NoScrollWithMouse,
    WindowFlags_NoCollapse                  = ImGuiWindowFlags_NoCollapse,
    WindowFlags_AlwaysAutoResize            = ImGuiWindowFlags_AlwaysAutoResize,
    WindowFlags_NoBackground                = ImGuiWindowFlags_NoBackground,
    WindowFlags_NoSavedSettings             = ImGuiWindowFlags_NoSavedSettings,
    WindowFlags_NoMouseInputs               = ImGuiWindowFlags_NoMouseInputs,
    WindowFlags_MenuBar                     = ImGuiWindowFlags_MenuBar,
    WindowFlags_HorizontalScrollbar         = ImGuiWindowFlags_HorizontalScrollbar,
    WindowFlags_NoFocusOnAppearing          = ImGuiWindowFlags_NoFocusOnAppearing,
    WindowFlags_NoBringToFrontOnFocus       = ImGuiWindowFlags_NoBringToFrontOnFocus,
    WindowFlags_AlwaysVerticalScrollbar     = ImGuiWindowFlags_AlwaysVerticalScrollbar,
    WindowFlags_AlwaysHorizontalScrollbar   = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
    WindowFlags_AlwaysUseWindowPadding      = ImGuiWindowFlags_AlwaysUseWindowPadding,
    WindowFlags_NoNavInputs                 = ImGuiWindowFlags_NoNavInputs,
    WindowFlags_NoNavFocus                  = ImGuiWindowFlags_NoNavFocus,
    WindowFlags_UnsavedDocument             = ImGuiWindowFlags_UnsavedDocument,
    WindowFlags_NoNav                       = ImGuiWindowFlags_NoNav,
    WindowFlags_NoDecoration                = ImGuiWindowFlags_NoDecoration,
    WindowFlags_NoInputs                    = ImGuiWindowFlags_NoInputs,

    // [Internal]
    WindowFlags_NavFlattened                = ImGuiWindowFlags_NavFlattened,
    WindowFlags_ChildWindow                 = ImGuiWindowFlags_ChildWindow,
    WindowFlags_Tooltip                     = ImGuiWindowFlags_Tooltip,
    WindowFlags_Popup                       = ImGuiWindowFlags_Popup,
    WindowFlags_Modal                       = ImGuiWindowFlags_Modal,
    WindowFlags_ChildMenu                   = ImGuiWindowFlags_ChildMenu

    // [Obsolete]
    //ImGuiWindowFlags_ShowBorders          = 1 << 7,   // --> Set style.FrameBorderSize=1.0f or style.WindowBorderSize=1.0f to enable borders around items or windows.
    //ImGuiWindowFlags_ResizeFromAnySide    = 1 << 17,  // --> Set io.ConfigWindowsResizeFromEdges=true and make sure mouse cursors are supported by back-end (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)
};

/** Font type */
using Font = ImFont;

} // namespace GUI

#endif // __GUI_IMGUI_COMMON_H__