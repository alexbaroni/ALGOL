project(tests)

include_directories(lib/gtest-1.7.0/googletest/include)
include_directories(lib/gtest-1.7.0/googlemock/include)

add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(basic_tests)
add_subdirectory(integer_tests)
add_subdirectory(perf_tests)
add_subdirectory(result_tests)
add_subdirectory(sort_tests)
add_subdirectory(sequence_tests)
add_subdirectory(stack_tests)
add_subdirectory(stream_tests)