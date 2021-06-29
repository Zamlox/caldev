/**
 * Author: 		Iosif Haidu
 * Description: Queue for widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"
#include "internal/gui/iwindow.h"
#include "internal/gui/widgets/queue/command.h"
#include <map>
#include <list>

namespace GUI {
namespace Widget {

/** Element type to store */
class StorageElem {
public:
    using Container = std::list<StorageElem>;
    using StorageIndex = Container::iterator;

    union {
        IWindow* pWindow;
        IWidget* pWidget;
    } widget;
    Id parentId;
    GuiElemType type;
    StorageIndex childFirst;
    StorageIndex childLast;
};

/**
 * Queue for all GUI widgets.
 * Not thread safe, to be used only within one thread.
 */
class Storage
{
public:
    /** Container type for widgets */
    using Container = StorageElem::Container;
    /** Index type of staorage */
    using Index = StorageElem::StorageIndex;
    /** Widget id, index */
    using Lookup = std::map<Id, StorageElem::StorageIndex>;

    Storage(bool hasSharedElemsP);

    ~Storage();

    /**
     * Add widget as child for a parent widget.
     * 
     * @param  {IWidget*} pWidgetP : widget to add
     * @param  {Id} parentIdP      : id of a parent widget
     */
    Index add(IWidget* pWidgetP, Id parentIdP);
    
    /**
     * Add window as child for a parent window.
     * 
     * @param  {IWindow*} pWindowP : window to add 
     * @param  {Id} parentIdP      : id of a parent window
     */
    Index add(IWindow* pWindowP, Id parentIdP);

    /**
     * Remove widget from storage
     * 
     * @param  {IWidget*} pWidgetP : widget to remove
     */
    void remove(IWidget* pWidgetP);

    /**
     * Remove window from storage.
     * 
     * @param  {IWindow*} pWindowP : window to remove
     */
    void remove(IWindow* pWindowP);

    /**
     * Get container elements.
     * 
     * @return {Container}  : container of elements
     */
    Container const& getElements();

    IWidget* getElement(Id idP);

private:
    /**
     * Add a storage element.
     * 
     * @param  {StorageElem} rElemP : element to add
     * @param  {Id} idP             : id of widget
     * @param  {Id} parentIdP       : id of parent widget
     */
    Index add(StorageElem& rElemP, Id idP, Id parentIdP);

    /**
     * Remove storage element.
     * 
     * @param  {Id} idP : id of element to remove
     */
    void remove(Id idP);

    /** Collection of widgets */
    Container widgetsM;
    /** Lookup in widgetsM based on widget id */
    Lookup lookupM;
    bool hasSharedElemsM;
};

} // namespace Widget
} // namespace GUI