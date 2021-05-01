/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/queue/storage.h"
#include "internal/gui/widgetfactory.h"

namespace GUI {
namespace Widget {

Storage::~Storage()
{
    for (auto& rElem : widgetsM)
    {
        if (rElem.type == GuiElemType::Widget)
        {
            WidgetFactory::instance().destroyWidget(rElem.widget.pWidget);
        }
        else
        {
            WidgetFactory::instance().destroyWindow(rElem.widget.pWindow);
        }
    }
}

Storage::Index Storage::add(IWidget* pWidgetP, Id parentIdP)
{
    StorageElem elem;
    elem.widget.pWidget = pWidgetP;
    elem.type = GuiElemType::Widget;
    return add(elem, pWidgetP->getId(), parentIdP);
}

Storage::Index Storage::add(IWindow* pWindowP, Id parentIdP)
{
    StorageElem elem;
    elem.widget.pWindow = pWindowP;
    elem.type = GuiElemType::Widget;
    return add(elem, pWindowP->getId(), parentIdP);
}

void Storage::remove(IWidget* pWidgetP)
{
    remove(pWidgetP->getId());
}

void Storage::remove(IWindow* pWindowP)
{
    remove(pWindowP->getId());
}

Storage::Container const& Storage::getElements()
{
    return widgetsM;
}

IWidget* Storage::getElement(Id idP)
{
    Lookup::const_iterator itLookup = lookupM.find(idP);
    if (itLookup != lookupM.end())
    {
        return itLookup->second->widget.pWidget;
    }
    return nullptr;
}

Storage::Index Storage::add(StorageElem& rElemP, Id idP, Id parentIdP)
{
    Storage::Index result{widgetsM.end()};
    if (widgetsM.empty())
    {
        rElemP.parentId = PARENT_NONE;
        rElemP.childFirst = widgetsM.end();
        rElemP.childLast = widgetsM.end();
        widgetsM.push_back(rElemP);
        result = widgetsM.begin();
        lookupM.insert(std::make_pair(idP, result));
    }
    else
    {
        rElemP.childFirst = widgetsM.end();
        rElemP.childLast = widgetsM.end();
        Lookup::const_iterator it{lookupM.find(parentIdP)};
        if (it == lookupM.end())
        {
            rElemP.parentId = PARENT_NONE;
            result = widgetsM.insert(widgetsM.end(), rElemP);
            lookupM.insert(std::make_pair(idP, result));
        }
        else
        {
            rElemP.parentId = parentIdP;
            Storage::Index newLast{it->second->childLast};
            if (newLast != widgetsM.end()) ++newLast;
            result = it->second->childLast = widgetsM.insert(newLast, rElemP);
            lookupM.insert(std::make_pair(idP, it->second->childLast));
            if (it->second->childFirst == widgetsM.end())
            {
                it->second->childFirst = it->second->childLast;
                it->second->childLast->childFirst = widgetsM.end();
                it->second->childLast->childLast = widgetsM.end();
            }
        }
    }
    return result;
}

void Storage::remove(Id idP)
{
    Lookup::const_iterator itLookup = lookupM.find(idP);
    if (itLookup != lookupM.end())
    {
        if (itLookup->second->parentId != INVALID_WIDGET_ID)
        {
            // get parent
            Lookup::iterator itParent = lookupM.find(itLookup->second->parentId);
            if (itParent != lookupM.end())
            {
                // if it's first child
                if (itParent->second->childFirst == itLookup->second)
                {
                    if (itParent->second->childFirst == itParent->second->childLast)
                    {
                        itParent->second->childFirst = widgetsM.end();
                        itParent->second->childLast = widgetsM.end();
                    }
                    else
                    {
                        itParent->second->childFirst++;
                    }
                }
                // if it's last child
                if (itParent->second->childLast == itLookup->second)
                {
                    for (Storage::Index it = itParent->second->childFirst; it != itParent->second->childLast; ++it)
                    {
                        Storage::Index itNext{it};
                        ++itNext;
                        if ( itNext == itParent->second->childLast)
                        {
                            itParent->second->childLast = it;
                            break;
                        }
                    }
                }
                // remove 
                widgetsM.erase(itLookup->second);
                lookupM.erase(itLookup);
            }
        }
        else
        {
            widgetsM.erase(itLookup->second);
            lookupM.erase(itLookup);
        }
    }
}

} // namespace Widget
} // namespace GUI
