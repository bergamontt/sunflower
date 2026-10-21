add_library(gui STATIC)

target_link_libraries(
    gui 
    PUBLIC 
        Qt6::Widgets
        core
    PRIVATE
        Qt6::Svg
)
    
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

        widgets/schedule/schedulepage.h
        widgets/schedule/schedulepage.cpp
        widgets/schedule/schedulepage.ui

        widgets/schedule/scheduleitem.h
        widgets/schedule/scheduleitem.cpp
        widgets/schedule/scheduleitem.ui

        widgets/schedule/scheduledialog.h
        widgets/schedule/scheduledialog.cpp
        widgets/schedule/scheduledialog.ui


        widgets/schedule/applicationshortlist.h
        widgets/schedule/applicationshortlist.cpp
        widgets/schedule/applicationshortlist.ui

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
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/schedule
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/statistics
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/settings
)

qt_add_resources(gui "gui"
    PREFIX "/gui"
    BASE "resources"
    FILES
        resources/delete.svg
        resources/done.svg
        resources/edit.svg
        resources/chart.svg
        resources/clock.svg
        resources/lock.svg
        resources/pause.svg
        resources/play.svg
        resources/plus.svg
        resources/settings.svg
        resources/sunflower.svg
)