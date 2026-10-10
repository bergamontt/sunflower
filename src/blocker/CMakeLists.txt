add_library(
        blocker STATIC
        blocker.h
        linuxblocker.h
        linuxblocker.cpp
)

target_link_libraries(
        blocker
        PUBLIC
        Qt6::Core
)