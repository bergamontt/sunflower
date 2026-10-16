add_executable(sunflower
    main.cpp
)

target_link_libraries(
    sunflower
    PRIVATE
        gui
        core
)