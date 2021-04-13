/**
 * Author: 		Iosif Haidu
 * Description: Thread safe map
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/mutex.h"
#include "extern/rebsdev/src/glue/face/face.h"
#include <map>
#include <functional>
#include <gsl/pointers.h>

namespace Tools
{

using namespace gsl;

/**
 * Thread safe map
 */
template <typename TKEY, typename TVALUE>
class SafeMap
{
private:
    using Map = std::map<TKEY, TVALUE>;

public:
    using ProcessFunc = std::function<void(TVALUE&)>;

    SafeMap()
    : pSyncExternalM{&syncMapM}
    {}
    SafeMap(not_null<Os::Mutex*> pSyncExternalP)
    : pSyncExternalM{pSyncExternalP.get()}
    {}
    
    void add(TKEY const& rKeyP, TVALUE const& rValueP)
    {
        pSyncExternalM->lock();
        mapM.insert(std::make_pair(rKeyP, rValueP));
        pSyncExternalM->unlock();
    }
    void remove(TKEY const& rKeyP)
    {
        pSyncExternalM->lock();
        mapM.erase(rKeyP);
        pSyncExternalM->unlock();
    }
    size_t count() const
    {
        return mapM.size();
    }
    bool get(TKEY const rKeyP, TVALUE& rValueP) const
    {
        bool found{false};
        pSyncExternalM->lock();
        found = getElem(rKeyP, rValueP);
        pSyncExternalM->unlock();
        return found;
    }
    bool process(TKEY const rKeyP, ProcessFunc funcP)
    {
        bool found{false};
        TVALUE elem;
        pSyncExternalM->lock();
        if ((found = getElem(rKeyP, elem)))
        {
            funcP(elem);
        }
        pSyncExternalM->unlock();
        return found;
    }
    void processAll(ProcessFunc funcP)
    {
        pSyncExternalM->lock();
        for(auto &rElem : mapM)
        {
            funcP(rElem.second);
        }
        pSyncExternalM->unlock();
    }

private:
    bool getElem(TKEY const rKeyP, TVALUE& rValueP) const
    {
        bool found{false};
        if (typename Map::const_iterator it = mapM.find(rKeyP); it != mapM.end())
        {
            found = true;
            rValueP = it->second;
        }
        return found;
    }

    Map mapM;
    Os::Mutex syncMapM;
    Os::Mutex* pSyncExternalM;
};

} // namespace Tools
