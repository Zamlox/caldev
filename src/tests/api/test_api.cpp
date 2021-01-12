/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"
#include "internal/errors/errors.h"
#include "internal/tools/logic.h"
#include <thread>

namespace {

using namespace std::chrono_literals;

class TestsAPI : public ::testing::Test
{
protected:

    void SetUp() override
    {
        Logic::check::showErrorMsg(false);
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
    EXPECT_EQ(guiEngineInit(guiType, guiThreadType), SUCCESS);
    EXPECT_EQ(guiEngineStop(), SUCCESS);
    EXPECT_EQ(guiEngineInit(99, guiThreadType), ERR_GUI_INVALID_GUI_ENGINE_TYPE);
    EXPECT_EQ(guiEngineStop(), ERR_GUI_ENGINE_NOT_INIT);
}

TEST_F(TestsAPI, CreateMainWindow) {
    guiEngineInit(guiType, guiThreadType);
    guiEngineStart();
    EXPECT_NE(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), 0);
    guiEngineStop();

    guiEngineInit(guiType, guiThreadType);
    guiEngineStart();
    EXPECT_GT(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), SUCCESS);
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