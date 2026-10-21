add_library(core STATIC)

target_link_libraries(
    core
    PRIVATE 
        monitor
        persistence
)

target_sources(
    core
    PUBLIC
        schedule/scheduleservice.h
        schedule/scheduleservice.cpp
        
        applicationlist/applicationlistservice.h
        applicationlist/applicationlistservice.cpp
)

target_include_directories(
    core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/applicationlist
        ${CMAKE_CURRENT_SOURCE_DIR}/schedule
)