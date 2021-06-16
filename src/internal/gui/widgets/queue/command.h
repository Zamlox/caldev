/**
 * Author: 		Iosif Haidu
 * Description: Queue for widgets commands
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/iwindow.h"
#include "internal/os/mutex.h"
#include "extern/rebsdev/src/glue/face/face.h"
#include <deque>

namespace GUI {
namespace Widget {

/** Type of commands */
enum class WidgetCommand {
    None,
    Create,
    Update,
    Remove,
    Stash,
    Unstash
};

/** Gui element type */
enum class GuiElemType {  
    Widget,
    Window
};

/**
 * Command element.
 */
class CommandElem
{
public:
    CommandElem(WidgetCommand typeP, Id parentIdP, IWindow* pWindowP)
        : type{typeP}
        , parentId{parentIdP}
        , guiType{GuiElemType::Window}
    {
        widget.pWindow = pWindowP;
    }
    CommandElem(WidgetCommand typeP, Id parentIdP, IWidget* pWidgetP)
        : type{typeP}
        , parentId{parentIdP}
        , guiType{GuiElemType::Widget}
    {
        widget.pWidget = pWidgetP;
    }
    CommandElem(WidgetCommand typeP)
        : type{typeP}
        , parentId{INVALID_WIDGET_ID}
        , guiType{GuiElemType::Widget}
    {
        widget.pWidget = nullptr;
    }

    WidgetCommand getType() const
    {
        return type;
    }
    Id getParentId() const 
    {
        return parentId;
    }
    IWidget* getWidget() const 
    {
        return widget.pWidget;
    }
    IWindow* getWindow() const
    {
        return widget.pWindow;
    }
    GuiElemType getGuiType() const
    {
        return guiType;
    }

private:
    WidgetCommand type;
    Id parentId;
    union {
        IWindow* pWindow;
        IWidget* pWidget;
    } widget;
    GlueFace face;              // for update command
    GuiElemType guiType;
};

/**
 * Queue for widget commands. Thread safe.
 */
class Command
{
public:
    /** Collection type */
    using Container = std::deque<CommandElem>;

    /**
     * Set command for a window in queue.
     * 
     * @param  {WidgetCommand} commandP : type of command
     * @param  {Id} parentIdP           : parent widget id
     * @param  {IWindow*} pWindowP      : window to add
     */
    void set(WidgetCommand commandP, Id parentIdP, IWindow* pWindowP);
    /**
     * Set command for a widget in queue.
     * 
     * @param  {WidgetCommand} commandP : type of command
     * @param  {Id} parentIdP           : parent widget id
     * @param  {IWidget*} pWidgetP      : widget to add
     */
    void set(WidgetCommand commandP, Id parentIdP, IWidget* pWidgetP);

    /**
     * Get command from queue.
     * 
     * @return {CommandElem}  : command element
     */
    CommandElem get();

private:
    /** Mutex to synchronize queue operations */
    Os::Mutex mutexM;
    /** Conatiner for commands */
    Container commandsM;
};

} // namespace Widget
} // namespace GUI