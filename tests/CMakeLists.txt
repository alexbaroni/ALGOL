project(tests)

include_directories(lib/gtest-1.7.0/googletest/include)
include_directories(lib/gtest-1.7.0/googlemock/include)

add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(basic_tests)