/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "mutex.h"
#include "semaphore.h"
#include "thread.h"
#include <vector>
#include <sstream>

namespace 
{

class ThreadTest : public ::testing::Test
{
protected:
    static constexpr int THREADS_COUNT = 100;

    void SetUp() override
    {
        for(int i = 0; i < THREADS_COUNT; i++)
        {
            threadsM.push_back(new Os::Thread);
            ASSERT_NE(threadsM[i], nullptr);
        }
        countM = 0;
    }
    void TearDown() override
    {
        for(auto thread : threadsM)
        {
            delete thread;
        }
    }

    std::vector<Os::IThread*> threadsM;
    int countM;
};

TEST_F(ThreadTest, Mutex) {
    Os::Mutex mutex;
    for(int i = 0; i < THREADS_COUNT; i++)
    {
        std::ostringstream oss;
        oss << "thread" << i;
        ASSERT_TRUE(threadsM[i]->create(oss.str().c_str(), [=](void* pParamP) {
            Os::Mutex* pMutex = static_cast<Os::Mutex*>(pParamP);
            pMutex->lock();
            countM++;
            pMutex->unlock();
            return nullptr;
        }, (void*)&mutex));
    }
    for(auto thread : threadsM)
    {
        thread->join();
    }
    ASSERT_EQ(countM, 100);
}

} // namespace anonymous