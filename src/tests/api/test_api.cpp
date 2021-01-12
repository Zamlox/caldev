/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"
#include <thread>

namespace {

using namespace std::chrono_literals;

class TestsAPI : public ::testing::Test
{
protected:

    void SetUp() override
    {
         guiType = static_cast<int>(Api::GuiType::GUI_OPENGL2);
         guiThreadType = static_cast<int>(Api::GuiEngineExecutionType::BKG_THREAD);
    }
    void TearDown() override
    {
    }

    int guiType;
    int guiThreadType;
};

TEST_F(TestsAPI, Initialization){
    EXPECT_EQ(guiEngineInit(guiType, guiThreadType), 0);
    EXPECT_EQ(guiEngineStop(), 0);
    EXPECT_EQ(guiEngineInit(guiType, guiThreadType), 0);
    guiEngineStop();
    EXPECT_NE(guiEngineInit(99, guiThreadType), 0);
    guiEngineStop();
}

TEST_F(TestsAPI, CreateMainWindow) {
    guiEngineInit(guiType, guiThreadType);
    EXPECT_NE(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), 0);
    guiEngineStop();
    EXPECT_EQ(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), Api::ERROR_API_NOT_INITIALIZED);
    guiEngineStop();
}

TEST_F(TestsAPI, HideMainWindow) {
#ifndef OS_MACOS
    guiEngineInit(guiType, guiThreadType);
    guiEngineStart();
    EXPECT_NE(createMainWindow("Test HideMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    std::this_thread::sleep_for(1s);
    hideMainWindow();
    std::this_thread::sleep_for(1s);
    guiEngineStop();
#endif
}

TEST_F(TestsAPI, ShowMainWindow) {
#ifndef OS_MACOS
    guiEngineInit(guiType, guiThreadType);
    guiEngineStart();
    EXPECT_NE(createMainWindow("Test ShowMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    std::this_thread::sleep_for(1s);
    hideMainWindow();
    std::this_thread::sleep_for(1s);
    showMainWindow();
    std::this_thread::sleep_for(1s);
    guiEngineStop();
#endif
}

} // anonymous namespace