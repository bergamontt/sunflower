add_library(gui STATIC
        widgets/settings/passwordconfirmation.h widgets/settings/passwordconfirmation.cpp widgets/settings/passwordconfirmation.ui)

target_link_libraries(
    gui 
    PUBLIC 
        core
        Qt6::Widgets
    PRIVATE
        Qt6::Svg
        Qt6::Charts
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

        widgets/statistics/windowstatistics.h
        widgets/statistics/windowstatistics.cpp
        widgets/statistics/windowstatistics.ui

        widgets/schedule/schedulepage.h
        widgets/schedule/schedulepage.cpp
        widgets/schedule/schedulepage.ui

        widgets/schedule/scheduleitem.h
        widgets/schedule/scheduleitem.cpp
        widgets/schedule/scheduleitem.ui

        widgets/schedule/scheduledialog.h
        widgets/schedule/scheduledialog.cpp
        widgets/schedule/scheduledialog.ui

        widgets/schedule/deletedialog.h
        widgets/schedule/deletedialog.cpp
        widgets/schedule/deletedialog.ui

        widgets/schedule/applicationshortlist.h
        widgets/schedule/applicationshortlist.cpp
        widgets/schedule/applicationshortlist.ui

        widgets/schedule/applicationdialog.h
        widgets/schedule/applicationdialog.cpp
        widgets/schedule/applicationdialog.ui

        widgets/schedule/applicationsdialog.h
        widgets/schedule/applicationsdialog.cpp
        widgets/schedule/applicationsdialog.ui

        widgets/settings/settingspage.h
        widgets/settings/settingspage.cpp
        widgets/settings/settingspage.ui

        widgets/settings/appearancesection.h
        widgets/settings/appearancesection.cpp
        widgets/settings/appearancesection.ui

        widgets/settings/strictmodetext.h
        widgets/settings/strictmodesection.h
        widgets/settings/strictmodesection.cpp
        widgets/settings/strictmodesection.ui
        widgets/settings/strictmodeutils.h
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
        resources/sunflower.svg
        resources/alarm-yellow.svg
        resources/pause-grey.svg
        resources/play-green.svg
        resources/style.qss
        resources/arrow.svg
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
        resources/on.svg
        resources/exe-file.svg
        resources/down-arrow.svg
        resources/up-arrow.svg
)