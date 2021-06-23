/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "modules/gui/opengl.h"
#include "internal/os/util.h"
#include "internal/errors/errors.h"
#include <thread>

#ifndef OS_MACOS
#include <filesystem>
#endif
#include <iostream>

#define GTEST_COUT std::cerr << "[ INFO     ] "

namespace
{

using namespace std::chrono_literals;

class TestsOpenGL : public ::testing::Test
{
protected:

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    static void* onLoad(void* pParamP)
    {
        GTEST_COUT << "STEP21" << std::endl;
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        GTEST_COUT << "STEP22" << std::endl;
        if (pOpenGL)
        {
            GTEST_COUT << "STEP23" << std::endl;
            pOpenGL->createMainWindow("Main thread window", 50, 50, 800, 600, 0xFF0000, true);
            GTEST_COUT << "STEP24" << std::endl;
        }
        GTEST_COUT << "STEP25" << std::endl;
        threadM.start();
        GTEST_COUT << "STEP26" << std::endl;
        return nullptr;
    }

    static void* onLoad1(void* pParamP)
    {
        GTEST_COUT << "STEP41" << std::endl;
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        GTEST_COUT << "STEP42" << std::endl;
        if (pOpenGL)
        {
            GTEST_COUT << "STEP43" << std::endl;
            pOpenGL->createMainWindow("Another main thread window", 10, 40, 600, 400, 0xFFFF00, true);
            GTEST_COUT << "STEP44" << std::endl;
        }
        GTEST_COUT << "STEP45" << std::endl;
        threadM.start();
        GTEST_COUT << "STEP46" << std::endl;
        return nullptr;
    }

    static void* stopMainThread(void* pParamP)
    {
        GTEST_COUT << "STEP81" << std::endl;
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        GTEST_COUT << "STEP82" << std::endl;
        if (pOpenGL)
        {
            GTEST_COUT << "STEP83" << std::endl;
            Os::Util::instance().msleep(1000);
            GTEST_COUT << "STEP84" << std::endl;
            pOpenGL->stop();
            GTEST_COUT << "STEP85" << std::endl;
        }
        GTEST_COUT << "STEP86" << std::endl;
        return nullptr;
    }

    static GUI::OpenGL opengl;
    static Os::Thread threadM;
};

GUI::OpenGL TestsOpenGL::opengl;
Os::Thread TestsOpenGL::threadM{"TestsOpenGL", nullptr, &TestsOpenGL::stopMainThread, &TestsOpenGL::opengl};


TEST_F(TestsOpenGL, StartMainThread) {
    GTEST_COUT << "STEP1" << std::endl;
    opengl.init(false);
    GTEST_COUT << "STEP2" << std::endl;
    onLoad(&opengl);
    GTEST_COUT << "STEP3" << std::endl;
    ASSERT_TRUE(opengl.startOnMainThread());
    GTEST_COUT << "STEP4" << std::endl;
    opengl.init(false);
    GTEST_COUT << "STEP5" << std::endl;
    onLoad1(&opengl);
    GTEST_COUT << "STEP6" << std::endl;
    ASSERT_TRUE(opengl.startOnMainThread());
    GTEST_COUT << "STEP7" << std::endl;
}

#ifndef OS_MACOS    // OSX does not support handling glfw main loop in different thread
TEST_F(TestsOpenGL, StartThread) {
    opengl.init(true);
    ASSERT_TRUE(opengl.startOnThread());
    int res = opengl.createMainWindow("Background thread window", 150, 150, 500, 300, 0x0000FF, true);
    ASSERT_NE(res, ERR_GUI_INVALID_WIDGET);
    std::this_thread::sleep_for(1s);
    opengl.stop();

    opengl.init(true);
    ASSERT_TRUE(opengl.startOnThread());
    res = opengl.createMainWindow("Another background thread window", 200, 200, 600, 200, 0x00FF00, true);
    ASSERT_NE(res, ERR_GUI_INVALID_WIDGET);
    std::this_thread::sleep_for(1s);
    opengl.stop();
}
#endif

#ifndef OS_MACOS    // missing filesystem
TEST_F(TestsOpenGL, CreateFont) {
    std::filesystem::path cwd = std::filesystem::current_path();
#ifdef OS_WINDOWS
    cwd.append("extern\\imgui\\misc\\fonts\\DroidSans.ttf");
#else
    cwd.append("extern/imgui/misc/fonts/DroidSans.ttf");
#endif
/*
    Bind::Rebol2::Default::instance().setFaceFont(
        "TestFont1",
        10,
        "Regular",
        {100, 100, 100},
        "Left",
        "Top",
        {10, 20},
        {21, 22},
        {13,14},
        cwd.string()
    );
    GUI::Font* pFont = opengl.createFont(Bind::Rebol2::Default::instance().getFont());
    ASSERT_NE(pFont, nullptr);
    GUI::Font* pFont1 = opengl.createFont(Bind::Rebol2::Default::instance().getFont());
    ASSERT_EQ(pFont, pFont1);
*/
}
#endif

}