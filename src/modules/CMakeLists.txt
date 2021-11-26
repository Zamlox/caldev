set(SOURCE_MODULES
        gui/igui.h
        gui/opengl.cpp
        gui/opengl.h)

target_sources(${CALDEV_SHARED} PRIVATE ${SOURCE_MODULES})
target_sources(${CALDEV_STATIC} PRIVATE ${SOURCE_MODULES})
