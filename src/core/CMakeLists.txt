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
    scanning/applicationscannerfactory.h
    scanning/applicationscannerfactory.cpp

    application/applicationservice.h
    application/applicationservice.cpp
)

if(WIN32)
    target_sources(core PRIVATE
        scanning/win32/win32applicationscanner.h
        scanning/win32/win32applicationscanner.cpp
    )
elseif(LINUX)
    target_sources(core PRIVATE
        scanning/linux/linuxapplicationscanner.h
        scanning/linux/linuxapplicationscanner.cpp
    )
endif()

target_include_directories(
    core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
