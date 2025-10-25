find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

set(SRC_LIST
    src/node.cpp
)

add_executable(node ${SRC_LIST})

target_link_libraries(node
    PRIVATE 
        range_queries::headers
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)

gtest_discover_tests(node
    PROPERTIES LABELS "unit"
)          
