add_library(
        monitor STATIC
        window.h
        monitor.h
        x11/x11window.h
        x11/x11window.cpp
)

target_link_libraries(
        monitor
        PUBLIC
        Qt6::Core
)