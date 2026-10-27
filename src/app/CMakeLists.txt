add_executable(sunflower
    main.cpp
)

set_target_properties(sunflower PROPERTIES
    AUTOMOC OFF
)

target_link_libraries(
    sunflower
    PRIVATE
        gui
        core
        persistence
        monitor
)