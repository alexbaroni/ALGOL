# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/io/pprint.hpp
    ../../include/algol/perf/operation_counter.hpp
    ../../include/algol/perf/duration.hpp
    ../../include/algol/perf/stopwatch.hpp
    ../../include/algol/perf/benchmark.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.perf.operation_counter_test ../perf_tests/operation_counter_test.cpp)
add_executable(test.perf.pprint_test ../perf_tests/pprint_test.cpp)
add_executable(test.perf.stopwatch_test ../perf_tests/stopwatch_test.cpp)

add_executable(test.perf.all_test ${SOURCE_FILES}
    ../perf_tests/operation_counter_test.cpp
    ../perf_tests/pprint_test.cpp
    ../perf_tests/stopwatch_test.cpp)

target_link_libraries(test.perf.operation_counter_test gtest gtest_main)
target_link_libraries(test.perf.pprint_test gtest gtest_main)
target_link_libraries(test.perf.stopwatch_test gtest gtest_main)
target_link_libraries(test.perf.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.perf.operation_counter_test test.perf.operation_counter_test)
add_test(test.perf.pprint_test test.perf.pprint_test)
add_test(test.perf.stopwatch_test test.perf.stopwatch_test)
add_test(test.perf.all_test test.perf.all_test)
