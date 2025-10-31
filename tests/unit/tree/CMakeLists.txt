find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

set(SRC_LIST
    src/tree.cpp
)

add_executable(tree ${SRC_LIST})

target_link_libraries(tree
    PRIVATE 
        range_queries::headers
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)

gtest_discover_tests(tree
    PROPERTIES LABELS "unit"
)          
