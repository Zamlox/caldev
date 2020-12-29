/**
 * Author: 		Iosif Haidu
 * Description: Thread safe map
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __TOOLS_SAFEMAP_H__
#define __TOOLS_SAFEMAP_H__

#include "internal/os/mutex.h"
#include <map>

namespace Tools
{

/**
 * Thread safe map
 */
template <typename TKEY, typename TVALUE>
class SafeMap
{
private:
    using Map = std::map<TKEY, TVALUE>;

public:
    SafeMap()
    : pSyncExternalM{&syncMapM}
    {}
    SafeMap(Os::Mutex* pSyncExternalP)
    : pSyncExternalM{pSyncExternalP}
    {}
    
    void add(TKEY const& rKeyP, TVALUE const& rValueP)
    {
        pSyncExternalM->lock();
        mapM.insert(std::make_pair(rKeyP, rValueP));
        pSyncExternalM->unlock();
    }
    bool get(TKEY const rKeyP, TVALUE& rValueP) const
    {
        bool found{false};
        pSyncExternalM->lock();
        typename Map::const_iterator it = mapM.find(rKeyP);
        if (it != mapM.end())
        {
            rValueP = it->second;
            found = true;
        }
        pSyncExternalM->unlock();
        return found;
    }

private:
    Map mapM;
    Os::Mutex syncMapM;
    Os::Mutex* pSyncExternalM;
};

} // namespace Tools

#endif // __TOOLS_SAFEMAP_H__