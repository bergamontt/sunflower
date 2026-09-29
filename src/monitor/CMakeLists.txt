add_library(
        monitor STATIC
        signalgenerator.h
)

target_link_libraries(
        monitor
        PUBLIC
        Qt6::Core
)