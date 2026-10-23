add_library(core
        monitoring/applicationmonitor.cpp
        monitoring/applicationmonitor.h
        monitoring/applicationinfo.h
        monitoring/applicationinfo.cpp
        
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