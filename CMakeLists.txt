cmake_minimum_required(VERSION 3.16)
project(Range_queries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STD_SET Range_queries_std_set)
set(RB_TREE Range_queries_rb_tree)
set(STD_SET_TIME Range_queries_std_set_time)
set(RB_TREE_TIME Range_queries_rb_tree_time)

add_library(range_queries_headers INTERFACE)
target_include_directories(range_queries_headers
    INTERFACE ${CMAKE_SOURCE_DIR}/include
)
add_library(range_queries::headers ALIAS range_queries_headers)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/driver.cpp
)

add_executable(${RB_TREE} ${SOURCES})
target_link_libraries(${RB_TREE} PRIVATE range_queries::headers)
target_compile_definitions(${RB_TREE} PRIVATE
    STD_SET_RUN=0
    RB_TREE_RUN=1
    TIMING_RUN=0
)

add_executable(${RB_TREE_TIME} ${SOURCES})
target_link_libraries(${RB_TREE_TIME} PRIVATE range_queries::headers)
target_compile_definitions(${RB_TREE_TIME} PRIVATE
    STD_SET_RUN=0
    RB_TREE_RUN=1
    TIMING_RUN=1
)

add_executable(${STD_SET} ${SOURCES})
target_link_libraries(${STD_SET} PRIVATE range_queries::headers)
target_compile_definitions(${STD_SET} PRIVATE
    STD_SET_RUN=1
    RB_TREE_RUN=0
    TIMING_RUN=0
)

add_executable(${STD_SET_TIME} ${SOURCES})
target_link_libraries(${STD_SET_TIME} PRIVATE range_queries::headers)
target_compile_definitions(${STD_SET_TIME} PRIVATE
    STD_SET_RUN=1
    RB_TREE_RUN=0
    TIMING_RUN=1
)


enable_testing()
add_subdirectory(tests)