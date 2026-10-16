add_library(core
    
)

target_link_libraries(
    core
    PRIVATE 
        monitor
        persistence
)