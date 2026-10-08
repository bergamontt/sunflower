add_library(
        monitor STATIC
        monitor.h
        linuxmonitor.h
        linuxmonitor.cpp
        linuxevent.h
        linuxevent.cpp
)

target_link_libraries(
        monitor
        PUBLIC
        Qt6::Core
)