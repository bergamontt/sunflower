add_library(gui STATIC)
    
target_sources(
    gui
    PUBLIC
        mainwindow.h
    PRIVATE
        mainwindow.cpp
        mainwindow.ui

        widgets/analytics/analyticspage.h
        widgets/analytics/analyticspage.cpp
        widgets/analytics/analyticspage.ui

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
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/analytics
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/block
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/settings
)

target_link_libraries(
    gui 
    PUBLIC 
        Qt6::Widgets
    PRIVATE
        Qt6::Svg
)

qt_add_resources(gui "gui"
    PREFIX "/gui"
    BASE "resources"
    FILES resources/sunflower.svg
)