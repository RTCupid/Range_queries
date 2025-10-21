cmake_minimum_required(VERSION 3.16)
project(Range_queries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp 
                                ${CMAKE_SOURCE_DIR}/src/driver.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

enable_testing()
add_subdirectory(tests)

option(RB_TREE_RUN "run red blue tree" ON)
option(STD_SET_RUN "run std::set" OFF)
option(TIMING_RUN "run timing" OFF)

message(STATUS "RB_TREE_RUN = ${RB_TREE_RUN}")
message(STATUS "STD_SET_RUN = ${STD_SET_RUN}")
message(STATUS "TIMING_RUN  = ${TIMING_RUN}")

target_compile_definitions(${PROJECT_NAME} PRIVATE
  RB_TREE_RUN=$<IF:$<BOOL:${RB_TREE_RUN}>,1,0>
  STD_SET_RUN=$<IF:$<BOOL:${STD_SET_RUN}>,1,0>
  TIMING_RUN=$<IF:$<BOOL:${TIMING_RUN}>,1,0>
)