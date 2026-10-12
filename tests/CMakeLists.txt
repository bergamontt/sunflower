project(test)

add_executable(
    tests
    persistence/main.cpp
    persistence/applicationtest.cpp
    persistence/activitytest.cpp
    persistence/dbtestfixture.h
)

target_link_libraries(
    tests
    persistence
    GTest::gtest
    Qt6::Core
    Qt6::Sql
)

include(GoogleTest)

enable_testing()
gtest_discover_tests(tests)