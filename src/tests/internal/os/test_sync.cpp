/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "mutex.h"
#include "semaphore.h"
#include "thread.h"
#include "util.h"
#include <vector>
#include <sstream>

namespace 
{

static constexpr int THREADS_COUNT{100};

class ThreadTest : public ::testing::Test
{
protected:

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
    Os::Mutex mutexM;
};

TEST_F(ThreadTest, MutexOn) {
    for(int i = 0; i < THREADS_COUNT; i++)
    {
        std::ostringstream oss;
        oss << "thread" << i;
        ASSERT_TRUE(
            threadsM[i]->create(
                oss.str().c_str(), 
                nullptr, 
                [=](void* pParamP) {
                    Os::Mutex* pMutex = static_cast<Os::Mutex*>(pParamP);
                    pMutex->lock();
                    int temp = countM;
                    Os::Util::instance().msleep(0);
                    temp++;
                    countM = temp;
                    pMutex->unlock();
                    return nullptr;
                }, 
                &mutexM
            )
        );
    }
    for(auto thread : threadsM)
    {
        thread->join();
    }
    ASSERT_EQ(countM, THREADS_COUNT);
}

TEST_F(ThreadTest, MutexOff) {
    for(int i = 0; i < THREADS_COUNT; i++)
    {
        std::ostringstream oss;
        oss << "thread" << i;
        ASSERT_TRUE(
            threadsM[i]->create(
                oss.str().c_str(), 
                nullptr, 
                [=](void* pParamP) {
                    int temp = countM;
                    Os::Util::instance().msleep(0);
                    temp++;
                    countM = temp;
                    return nullptr;
                }, 
                nullptr
            )
        );
    }
    for(auto thread : threadsM)
    {
        thread->join();
    }
    ASSERT_NE(countM, THREADS_COUNT);
}

} // namespace anonymous