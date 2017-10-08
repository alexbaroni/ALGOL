# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/stream/istream_range.hpp
    ../../include/algol/stream/lines_range.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.stream.istream_range_test ../stream_tests/istream_range_test.cpp)
add_executable(test.stream.lines_range_test ../stream_tests/lines_range_test.cpp)

add_executable(test.stream.all_test ${SOURCE_FILES}
    ../stream_tests/istream_range_test.cpp
    ../stream_tests/lines_range_test.cpp)

target_link_libraries(test.stream.istream_range_test gtest gtest_main)
target_link_libraries(test.stream.lines_range_test gtest gtest_main)
target_link_libraries(test.stream.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.stream.istream_range_test test.stream.istream_range_test)
add_test(test.stream.lines_range_test test.stream.lines_range_test)
add_test(test.stream.all_test test.stream.all_test)
