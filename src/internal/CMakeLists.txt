set(SOURCE_INTERNAL_ERRORS
        errors/errors.h
        )

set(SOURCE_INTERNAL_GUI
        gui/imgui/common.h
        gui/imgui/common.cpp
        gui/imgui/window.h
        gui/imgui/window.cpp
#        gui/layout/cell/icell.h
#        gui/layout/cell/cells.h
#        gui/layout/cell/cells.cpp
#        gui/layout/cell/cellbase.h
#        gui/layout/cell/celltype.h
        gui/layout/format/alignment.h
        gui/layout/format/format.h
        gui/render/renderbuffer.h
        gui/render/renderbuffer.cpp
        gui/render/renderbuffering.h
        gui/render/renderbuffering.cpp
        gui/widgets/queue/command.cpp
        gui/widgets/queue/command.h
        gui/widgets/queue/storage.cpp
        gui/widgets/queue/storage.h
        gui/widgets/area.cpp
        gui/widgets/area.h
        gui/widgets/button.cpp
        gui/widgets/button.h
        gui/widgets/checkbox.cpp
        gui/widgets/checkbox.h
        gui/widgets/combo.cpp
        gui/widgets/combo.h
        gui/widgets/field.cpp
        gui/widgets/field.h
        gui/widgets/image.cpp
        gui/widgets/image.h
        gui/widgets/label.cpp
        gui/widgets/label.h
        gui/widgets/radio.cpp
        gui/widgets/radio.h
        gui/basewidget.h
        gui/irender.h
        gui/iresize.h
        gui/iwidget.h
        gui/iwindow.h
        gui/renderer.cpp
        gui/renderer.h
        gui/resize.cpp
        gui/resize.h
        gui/widgetfactory.cpp
        gui/widgetfactory.h
        gui/window.cpp
        gui/window.h
        )

set(SOURCE_INTERNAL_OS_LINUX
        os/linux/barrier.cpp
        os/linux/barrier.h
        os/linux/mutex.cpp
        os/linux/mutex.h
        os/linux/thread.cpp
        os/linux/thread.h
        os/linux/util.cpp
        os/linux/util.h
        )
set(SOURCE_INTERNAL_OS_WINDOWS
        os/windows/barrier.cpp
        os/windows/barrier.h
        os/windows/mutex.cpp
        os/windows/mutex.h
        os/windows/thread.cpp
        os/windows/thread.h
        os/windows/util.cpp
        os/windows/util.h
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(SOURCE_INTERNAL_OS ${SOURCE_INTERNAL_OS_WINDOWS})
else()
    set(SOURCE_INTERNAL_OS ${SOURCE_INTERNAL_OS_LINUX})
endif()
list(APPEND SOURCE_INTERNAL_OS
        os/barrier.cpp
        os/barrier.h
        os/ibarrier.h
        os/imutex.h
        os/ithread.h
        os/iutil.h
        os/lock_guard.h
        os/mutex.cpp
        os/mutex.h
        os/thread.cpp
        os/thread.h
        os/util.cpp
        os/util.h
        )

set(SOURCE_INTERNAL_TOOLS
        tools/logic.cpp
        tools/logic.h
        tools/safemap.h
        )

target_sources(${CALDEV_SHARED} PRIVATE
        ${SOURCE_INTERNAL_ERRORS}
        ${SOURCE_INTERNAL_GUI}
        ${SOURCE_INTERNAL_OS}
        ${SOURCE_INTERNAL_TOOLS}
        )
target_sources(${CALDEV_STATIC} PRIVATE
        ${SOURCE_INTERNAL_ERRORS}
        ${SOURCE_INTERNAL_GUI}
        ${SOURCE_INTERNAL_OS}
        ${SOURCE_INTERNAL_TOOLS}
        )
