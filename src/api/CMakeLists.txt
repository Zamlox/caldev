set(SOURCE_API
        api.h
        api.cpp
        imp/apiconst.h
        imp/apiimp.h
        imp/apiimp.cpp
        )

target_sources(${CALDEV_SHARED} PRIVATE ${SOURCE_API})
target_sources(${CALDEV_STATIC} PRIVATE ${SOURCE_API})
