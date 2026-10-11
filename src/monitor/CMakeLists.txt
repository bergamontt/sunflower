add_library(
        monitor STATIC
        window.h
        monitor.h
)

target_link_libraries(
        monitor
        PUBLIC
        Qt6::Core
)