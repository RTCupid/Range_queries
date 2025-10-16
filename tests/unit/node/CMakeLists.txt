find_package(GTest REQUIRED)
include(GoogleTest)

aux_source_directory(./src SRC_LIST)

add_executable(node ${SRC_LIST})

target_link_libraries(node
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(node
                      PRIVATE ${TEST_INCLUDE_DIR}
                      PRIVATE ${TEST_INCLUDE_DIR}/node)                  
