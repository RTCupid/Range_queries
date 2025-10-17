find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(generator generator.cpp)

target_link_libraries(generator
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)
