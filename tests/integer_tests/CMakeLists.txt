# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/integer/integer_interval.hpp
    ../../include/algol/integer/integer_interval_range.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.integer.integer_interval_test ../integer_tests/integer_interval_test.cpp)
add_executable(test.integer.integer_interval_range_test ../integer_tests/integer_interval_range_test.cpp)

add_executable(test.integer.all_test ${SOURCE_FILES}
    ../integer_tests/integer_interval_test.cpp
    ../integer_tests/integer_interval_range_test.cpp)

target_link_libraries(test.integer.integer_interval_test gtest gtest_main)
target_link_libraries(test.integer.integer_interval_range_test gtest gtest_main)
target_link_libraries(test.integer.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.integer.integer_interval_test test.integer.integer_interval_test)
add_test(test.integer.integer_interval_range_test test.integer.integer_interval_range_test)
add_test(test.integer.all_test test.integer.all_test)
