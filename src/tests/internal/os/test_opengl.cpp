/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "opengl.h"
#include "util.h"

namespace
{

TEST(TestsOpenGL, Init) {
    GUI::OpenGL opengl;
    ASSERT_TRUE(opengl.start());
    int res = opengl.createMainWindow("Hello", 50, 50, 800, 600, 0xFF0000, false);
    ASSERT_NE(res, GUI::INVALID_WIDGET_ID);
    Os::Util::instance().msleep(100);
    opengl.closeMainWindow();
}

}

