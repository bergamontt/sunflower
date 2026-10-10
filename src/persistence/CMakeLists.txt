add_library(persistence STATIC)

target_sources(persistence PUBLIC
    activity/activity.h
    activity/activitysql.h
    activity/iactivitydao.h
    activity/activitydao.h
    activity/activitydao.cpp
    activity/activitymapper.h

    application/application.h
    application/applicationsql.h
    application/applicationdao.h
    application/iapplicationdao.h
    application/applicationdao.cpp
    application/applicationmapper.h

    applicationlist/applicationlist.h
    applicationlist/applicationlistsql.h
    applicationlist/applicationlistdao.h
    applicationlist/iapplicationlistdao.h
    applicationlist/applicationlistdao.cpp
    applicationlist/applicationlistmapper.h
    
    pomodoro/pomodoro.h
    pomodoro/pomodorodao.h
    pomodoro/ipomodorodao.h
    pomodoro/pomodorosql.h
    pomodoro/pomodorodao.cpp
    pomodoro/pomodoromapper.h

    schedule/schedule.h
    schedule/schedulesql.h
    schedule/ischeduledao.h
    schedule/scheduledao.h
    schedule/scheduledao.cpp
    schedule/schedulemapper.h

    dbconnection.cpp
    dbconnection.h
    utils.h
)

target_include_directories(
    persistence
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    persistence
    PUBLIC
        Qt6::Core
        Qt6::Sql
)