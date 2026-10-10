project(test)

add_executable(
    tests
    persistence/applicationtest.cpp
)

target_link_libraries(
    tests
    persistence
    GTest::gtest_main
)

include(GoogleTest)

enable_testing()
gtest_discover_tests(tests)