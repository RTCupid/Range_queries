find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(generator generator.cpp)

target_link_libraries(generator
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
    PRIVATE Threads::Threads
)

add_test(NAME end_to_end.generator COMMAND generator)
set_tests_properties(end_to_end.generator PROPERTIES LABELS "end_to_end")