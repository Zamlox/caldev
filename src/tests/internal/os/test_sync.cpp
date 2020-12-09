/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "mutex.h"
#include "barrier.h"
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
    Os::Barrier barrierM;
};

TEST_F(ThreadTest, MutexOn) {
    for(int i = 0; i < THREADS_COUNT; i++)
    {
        std::ostringstream oss;
        oss << "thread" << i;
        threadsM.push_back(new Os::Thread{
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
        });
        ASSERT_NE(threadsM[i], nullptr);
        ASSERT_TRUE(threadsM[i]->start());
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
        threadsM.push_back(new Os::Thread{
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
        });
        ASSERT_TRUE(threadsM[i]->start());
    }
    for(auto thread : threadsM)
    {
        thread->join();
    }
    ASSERT_NE(countM, THREADS_COUNT);
}

TEST_F(ThreadTest, BarrierOn) {
    threadsM.push_back(new Os::Thread{
        "thread0", 
        nullptr, 
        [=](void* pParamP) {
            Os::Barrier* pBarrier = static_cast<Os::Barrier*>(pParamP);
            countM++;
            pBarrier->wait();
            return nullptr;
        }, 
        &barrierM
    });
    threadsM.push_back(new Os::Thread{
        "thread1", 
        nullptr, 
        [=](void* pParamP) {
            Os::Barrier* pBarrier = static_cast<Os::Barrier*>(pParamP);
            pBarrier->signal();
            Os::Util::instance().msleep(100);
            return nullptr;
        }, 
        &barrierM
    });
    ASSERT_TRUE(threadsM[0]->start());
    ASSERT_TRUE(threadsM[1]->start());
    threadsM[1]->join();
    ASSERT_EQ(countM, 1);
}

TEST_F(ThreadTest, BarrierOff) {
    threadsM.push_back(new Os::Thread{
        "thread0", 
        nullptr, 
        [=](void* pParamP) {
            Os::Barrier* pBarrier = static_cast<Os::Barrier*>(pParamP);
            pBarrier->wait();
            countM++;
            return nullptr;
        }, 
        &barrierM
    });
    threadsM.push_back(new Os::Thread{
        "thread1", 
        nullptr, 
        [=](void* pParamP) {
            Os::Util::instance().msleep(100);
            return nullptr;
        }, 
        nullptr
    });
    ASSERT_TRUE(threadsM[0]->start());
    ASSERT_TRUE(threadsM[1]->start());
    threadsM[1]->join();
    ASSERT_EQ(countM, 0);
}

} // namespace anonymous