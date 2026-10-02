add_library(persistence STATIC)

target_sources(persistence PUBLIC
    activity/activity.h
    activity/activitysql.h
    activity/iactivitydao.h
    activity/activitydao.h
    activity/activitydao.cpp

    application/application.h
    application/applicationsql.h
    application/applicationdao.h
    application/iapplicationdao.h
    application/applicationdao.cpp

    applicationlist/applicationlist.h
    applicationlist/applicationlistsql.h
    applicationlist/applicationlistdao.h
    applicationlist/iapplicationlistdao.h
    applicationlist/applicationlistdao.cpp
    
    pomodoro/pomodoro.h
    pomodoro/pomodorodao.h
    pomodoro/ipomodorodao.h
    pomodoro/pomodorosql.h
    pomodoro/pomodorodao.cpp

    schedule/schedule.h
    schedule/schedulesql.h
    schedule/ischeduledao.h
    schedule/scheduledao.h
    schedule/scheduledao.cpp

    dbconnection.cpp
    dbconnection.h
    
    activity/activitymapper.h
    application/applicationmapper.h
    applicationlist/applicationlistmapper.h
    pomodoro/pomodoromapper.h
    schedule/schedulemapper.h
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
    PRIVATE
        Qt6::Sql
)