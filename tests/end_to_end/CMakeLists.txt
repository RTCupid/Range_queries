find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(generator generator.cpp)

target_link_libraries(generator
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
    PRIVATE Threads::Threads
)

add_test(
    NAME end_to_end 
    COMMAND ${CMAKE_COMMAND} -E env VERBOSE=1 bash ${CMAKE_CURRENT_SOURCE_DIR}/end_to_end.sh
)

set_tests_properties(end_to_end PROPERTIES 
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    LABELS "end_to_end"
)