/**
 * Author: 		Iosif Haidu
 * Description: Base widget storage thread safe
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_BASEWIDGETSTORAGE_H__
#define __GUI_BASEWIDGETSTORAGE_H__

#include "internal/gui/storage/iwidgetstorage.h"
#include "internal/gui/irender.h"
#include "internal/tools/safemap.h"
#include "extern/imgui/imgui.h"

namespace GUI
{
namespace Storage
{

/**
 * Class used to group common functions of storage.
 * Add more methods if needed to process widgets within storage.
 */
template <typename T>
class BaseWidgetStorage : public IWidgetStorage<T>,
                          public IRender
{
public:
    /** Storage type */
    using StorageKey    = typename IWidgetStorage<T>::StorageKey;
    using StorageElem   = T*;
    using Storage       = Tools::SafeMap<StorageKey, StorageElem>;

    BaseWidgetStorage()
        : renderFuncM{[](StorageElem widgetP){
            widgetP->render();
        }}
        , updateFuncM{[](StorageElem widgetP){
            // TODO: implement 'update()' for widgets
            //widgetP->update();
        }}
    {}

    /** see IWidgetStorage::remove() */
    void remove(StorageKey idP) override
    {
        storageM.remove(idP);
    }
    /** see IWidgetStorage::count() */
    size_t count() const override
    {
        return storageM.count();
    }

    /** see IRender::render() */
    void render() override
    {
        storageM.processAll(renderFuncM);
    }

    /** see IWidgetStorage::update() */
    void update(StorageKey keyP) override
    {
        storageM.process(keyP, updateFuncM);
    }

protected:
    /** Storage for widgets */
    Storage storageM;
    /** Function to render widgets */
    typename Storage::ProcessFunc renderFuncM;
    /** Function to update widget */
    typename Storage::ProcessFunc updateFuncM;
};

} // namespace Storage
} // namespace Gui

#endif // __GUI_BASEWIDGETSTORAGE_H__