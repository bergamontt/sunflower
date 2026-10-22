add_library(core)

target_sources(core PUBLIC
    settingsservice.h
    settingsservice.cpp
    settingskeys.h
    lockpolicy.h
    lockpolicy.cpp
)

target_link_libraries(
    core
    PRIVATE 
        monitor
        persistence
)