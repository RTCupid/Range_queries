find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

aux_source_directory(./src SRC_LIST)

add_executable(node ${SRC_LIST})

target_include_directories(node PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(node
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
    PRIVATE Threads::Threads
)

gtest_discover_tests(node
    DISCOVERY_MODE POST_BUILD
    PROPERTIES LABELS "unit"
)          
