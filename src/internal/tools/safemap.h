/**
 * Author: 		Iosif Haidu
 * Description: Thread safe map
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __TOOLS_SAFEMAP_H__
#define __TOOLS_SAFEMAP_H__

#include <map>
#include <mutex>
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
    using Mutex = std::recursive_mutex;

public:
    SafeMap()
    : pSyncExternalM{&syncMapM}
    {}
    SafeMap(not_null<Mutex*> pSyncExternalP)
    : pSyncExternalM{pSyncExternalP.get()}
    {}
    
    void add(TKEY const& rKeyP, TVALUE const& rValueP)
    {
        const std::lock_guard<Mutex> lock{*pSyncExternalM};
        mapM.insert(std::make_pair(rKeyP, rValueP));
    }
    bool get(TKEY const rKeyP, TVALUE& rValueP) const
    {
        bool found{false};
        const std::lock_guard<Mutex> lock{*pSyncExternalM};
        if (typename Map::const_iterator it = mapM.find(rKeyP); it != mapM.end())
        {
            rValueP = it->second;
            found = true;
        }
        return found;
    }

private:
    Map mapM;
    Mutex syncMapM;
    Mutex* pSyncExternalM;
};

} // namespace Tools

#endif // __TOOLS_SAFEMAP_H__