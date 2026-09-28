add_library(
    persistence STATIC
    model/activity.h
    model/applicationlist.h
    model/application.h
    dbconnection.cpp
    dbconnection.h
    model/pomodoro.h
    model/schedule.h
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