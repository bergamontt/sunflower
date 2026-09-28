add_library(
    persistence STATIC
    models/activity.h
    models/applicationlist.h
    models/application.h
    dbconnection.cpp
    dbconnection.h
    models/pomodoro.h
    models/schedule.h
    sql/activitysql.h
    sql/applicationsql.h
    sql/applicationlistsql.h
    sql/pomodorosql.h
    sql/schedulesql.h
)

target_link_libraries(
    persistence
    PUBLIC
        Qt6::Core
    PRIVATE:
        Qt6::Sql
)