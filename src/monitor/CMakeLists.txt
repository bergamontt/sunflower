add_library(
        monitor STATIC
        signalgenerator.h
        monitor.h
        linuxmonitor.h
)

target_link_libraries(
        monitor
        PUBLIC
        Qt6::Core
)