add_library(persistence STATIC
    
    activity/activity.h
    activity/activitysql.h
    activity/activitydao.h
    activity/activitydao.cpp

    application/application.h
    application/applicationsql.h
    application/applicationdao.h
    application/applicationdao.cpp

    applicationlist/applicationlist.h
    applicationlist/applicationlistsql.h
    applicationlist/applicationlistdao.h
    applicationlist/applicationlistdao.cpp
    
    pomodoro/pomodoro.h
    pomodoro/pomodorodao.h
    pomodoro/pomodorosql.h
    pomodoro/pomodorodao.cpp

    schedule/schedule.h
    schedule/schedulesql.h
    schedule/scheduledao.h
    schedule/scheduledao.cpp

    dbconnection.cpp
    dbconnection.h
)

target_link_libraries(
    persistence
    PUBLIC
        Qt6::Core
    PRIVATE:
        Qt6::Sql
)