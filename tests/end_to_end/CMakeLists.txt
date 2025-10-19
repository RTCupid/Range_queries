add_executable(generator generator.cpp)

target_link_libraries(generator
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      m)
