add_library(core)

target_sources(core PUBLIC
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

        scanning/applicationscanner.h
        scanning/applicationscanner.cpp

        application/applicationservice.h
        application/applicationservice.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    core
    PUBLIC
        monitor
        persistence
)