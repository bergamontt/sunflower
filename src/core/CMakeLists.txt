add_library(core)

target_sources(core PUBLIC
    settings/settingsservice.h
    settings/settingsservice.cpp
    settings/settingskeys.h
    settings/lockpolicy.h
    settings/lockpolicy.cpp
)

target_link_libraries(
    core
    PRIVATE 
        monitor
        persistence
)