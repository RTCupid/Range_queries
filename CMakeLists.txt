cmake_minimum_required(VERSION 3.16)
project(Range_queries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STD_SET Range_queries_std_set)
set(RB_TREE Range_queries_rb_tree)
set(RB_TREE_LOG Range_queries_rb_tree_log)
set(STD_SET_TIME Range_queries_std_set_time)
set(RB_TREE_TIME Range_queries_rb_tree_time)
set(RB_TREE_LOG_TIME  Range_queries_rb_tree_log_time)

add_library(range_queries_headers INTERFACE)
target_include_directories(range_queries_headers
    INTERFACE ${CMAKE_SOURCE_DIR}/include
)
add_library(range_queries::headers ALIAS range_queries_headers)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

function(add_range_query_executable TARGET_NAME)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs DEFINITIONS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable(${TARGET_NAME} ${ARG_UNPARSED_ARGUMENTS})
    target_link_libraries(${TARGET_NAME} PRIVATE range_queries::headers)

    if(ARG_DEFINITIONS)
        target_compile_definitions(${TARGET_NAME} PRIVATE ${ARG_DEFINITIONS})
    endif()
endfunction()


add_range_query_executable(${RB_TREE}          ${SOURCES} DEFINITIONS RB_TREE_RUN)
add_range_query_executable(${RB_TREE_TIME}     ${SOURCES} DEFINITIONS TIMING_RUN)
add_range_query_executable(${STD_SET}          ${SOURCES} DEFINITIONS STD_SET_RUN)
add_range_query_executable(${STD_SET_TIME}     ${SOURCES} DEFINITIONS STD_SET_RUN TIMING_RUN)
# add_range_query_executable(${RB_TREE_LOG}      ${SOURCES} DEFINITIONS RB_TREE_LOG_RUN)
# add_range_query_executable(${RB_TREE_LOG_TIME} ${SOURCES} DEFINITIONS RB_TREE_LOG_RUN TIMING_RUN)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${RB_TREE} PRIVATE -mllvm -inline-threshold=500)
    target_compile_options(${RB_TREE_TIME} PRIVATE -mllvm -inline-threshold=500)
    target_compile_options(${STD_SET} PRIVATE -mllvm -inline-threshold=500)
    target_compile_options(${STD_SET_TIME} PRIVATE -mllvm -inline-threshold=500)
endif()

enable_testing()
add_subdirectory(tests)
