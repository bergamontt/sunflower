add_library(core STATIC)

target_link_libraries(
    core
    PUBLIC
        monitor
        persistence
)

target_sources(
    core
    PUBLIC
        schedule/scheduleservice.h
        schedule/scheduleservice.cpp

        application/applicationservice.h
        application/applicationservice.cpp
        
        applicationlist/applicationlistservice.h
        applicationlist/applicationlistservice.cpp
        
        monitoring/applicationmonitor.cpp
        monitoring/applicationmonitor.h
        monitoring/applicationinfo.h
        monitoring/applicationinfo.cpp
        
        settings/settingsservice.h
        settings/settingsservice.cpp
        settings/settingskeys.h
        settings/lockpolicy.h
        settings/lockpolicy.cpp

        password/passwordservice.h
        password/passwordservice.cpp
)

target_include_directories(
    core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/application
        ${CMAKE_CURRENT_SOURCE_DIR}/applicationlist
        ${CMAKE_CURRENT_SOURCE_DIR}/schedule
        ${CMAKE_CURRENT_SOURCE_DIR}/monitoring
        ${CMAKE_CURRENT_SOURCE_DIR}/settings
        ${CMAKE_CURRENT_SOURCE_DIR}/password
)