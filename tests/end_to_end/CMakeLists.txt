find_package(Threads REQUIRED)

add_executable(generator generator.cpp)

target_link_libraries(generator
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