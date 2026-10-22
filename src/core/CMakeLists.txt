add_library(core
        monitoring/applicationmonitor.cpp
        monitoring/applicationmonitor.h
        monitoring/applicationinfo.h
        monitoring/applicationinfo.cpp
)

target_link_libraries(
    core
    PRIVATE 
        monitor
        persistence
)