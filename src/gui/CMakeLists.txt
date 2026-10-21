add_library(gui STATIC)
    
target_sources(
    gui
    PUBLIC
        mainwindow.h
    PRIVATE
        mainwindow.cpp
        mainwindow.ui

        widgets/statistics/statisticspage.h
        widgets/statistics/statisticspage.cpp
        widgets/statistics/statisticspage.ui

        widgets/statistics/windowstatistics.h
        widgets/statistics/windowstatistics.cpp
        widgets/statistics/windowstatistics.ui

        widgets/block/blockpage.h
        widgets/block/blockpage.cpp
        widgets/block/blockpage.ui

        widgets/settings/settingspage.h
        widgets/settings/settingspage.cpp
        widgets/settings/settingspage.ui

        widgets/settings/appearancesection.h
        widgets/settings/appearancesection.cpp
        widgets/settings/appearancesection.ui

        widgets/settings/strictmodesection.h
        widgets/settings/strictmodesection.cpp
        widgets/settings/strictmodesection.ui
)   

target_include_directories(
    gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/statistics
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/block
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/settings
)

target_link_libraries(
    gui 
    PUBLIC 
        Qt6::Widgets
    PRIVATE
        Qt6::Svg
        Qt6::Charts
)

qt_add_resources(gui "gui"
    PREFIX "/gui"
    BASE "resources"
    FILES
        resources/alarm-yellow.svg
        resources/pause-grey.svg
        resources/play-green.svg
        resources/sunflower.svg
)