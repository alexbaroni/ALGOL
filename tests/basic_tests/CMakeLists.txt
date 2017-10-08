# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/ds/array/array.hpp
    ../../include/algol/ds/list/list.hpp
    ../../include/algol/ds/stack/fixed_stack.hpp
    ../../include/algol/ds/stack/linked_stack.hpp
    ../../include/algol/ds/stack/array_stack.hpp
    ../../include/algol/ds/stack/stack.hpp
    ../../include/algol/eval/eval.hpp
    ../../include/algol/eval/eval_tokenizer.hpp
    ../../include/algol/func/function.hpp
    ../../include/algol/integer/integer_interval.hpp
    ../../include/algol/integer/integer_interval_range.hpp
    ../../include/algol/io/pprint.hpp
    ../../include/algol/math/math.hpp
    ../../include/algol/perf/operation_counter.hpp
    ../../include/algol/perf/duration.hpp
    ../../include/algol/perf/stopwatch.hpp
    ../../include/algol/sequence/generator/arithmetic_progression_generator.hpp
    ../../include/algol/sequence/generator/collatz_generator.hpp
    ../../include/algol/sequence/generator/factorial_generator.hpp
    ../../include/algol/sequence/generator/fibonacci_generator.hpp
    ../../include/algol/sequence/generator/geometric_progression_generator.hpp
    ../../include/algol/sequence/generator/iota_generator.hpp
    ../../include/algol/sequence/sequence.hpp
    ../../include/algol/stream/istream_range.hpp
    ../../include/algol/stream/lines_range.hpp
    ../../include/algol/result/result.hpp
    ../../include/algol/eval/eval.hpp
    ../../include/algol/result/to.hpp
    ../../include/algol/perf/benchmark.hpp
    ../../include/algol/ds/stack/concepts.hpp
    ../../include/algol/algorithms/stack/sort.hpp
    ../../include/algol/algorithms/recursion/factorial.hpp
    ../../include/algol/utility.hpp
    ../../include/algol/algorithms/sort/bogo_sort.hpp
    ../../include/algol/algorithms/recursion/permutation.hpp
    ../../include/algol/algorithms/shuffle/fisher_yates.hpp
    ../../include/algol/algorithms/shuffle/sattolo_cycle.hpp
    ../../include/algol/algorithms/sort/bubble_sort.hpp
    ../../include/algol/algorithms/algorithm.hpp ../../include/algol/algorithms/sort/insertion_sort.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.basic.algorithm_test algorithm_test.cpp)
add_executable(test.basic.array_test array_test.cpp)
add_executable(test.basic.function_test function_test.cpp)
add_executable(test.basic.math_test math_test.cpp)
add_executable(test.basic.permutation_test permutation_test.cpp)

add_executable(test.all_test ${SOURCE_FILES} array_test.cpp ../perf_tests/stopwatch_test.cpp ../perf_tests/pprint_test.cpp
    ../perf_tests/operation_counter_test.cpp function_test.cpp ../integer_tests/integer_interval_test.cpp ../integer_tests/integer_interval_range_test.cpp
    ../stream_tests/istream_range_test.cpp ../stream_tests/lines_range_test.cpp ../sequence_tests/sequence_test.cpp ../sequence_tests/fibonacci_generator_test.cpp
    ../sequence_tests/iota_generator_test.cpp math_test.cpp ../sequence_tests/collatz_generator_test.cpp
    ../sequence_tests/arithmetic_progression_generator_test.cpp
    ../sequence_tests/geometric_progression_generator_test.cpp ../sequence_tests/factorial_generator_test.cpp ../stack_tests/linked_stack_test.cpp
    ../stack_tests/fixed_stack_test.cpp ../result_tests/result_test.cpp ../result_tests/to_test.cpp ../stack_tests/array_stack_test.cpp
    ../sort_tests/bogo_sort_test.cpp ../sort_tests/bubble_sort_test.cpp ../sort_tests/selection_sort_test.cpp
    permutation_test.cpp algorithm_test.cpp)

target_link_libraries(test.basic.array_test gtest gtest_main)
target_link_libraries(test.basic.function_test gtest gtest_main)
target_link_libraries(test.basic.math_test gtest gtest_main)
target_link_libraries(test.basic.permutation_test ${Boost_LIBRARIES} gtest gtest_main)
target_link_libraries(test.basic.algorithm_test gtest gtest_main)
target_link_libraries(test.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.basic.algorithm_test test.basic.algorithm_test)
add_test(test.basic.array_test test.basic.array_test)
add_test(test.basic.function_test test.basic.function_test)
add_test(test.basic.math_test test.basic.math_test)
add_test(test.basic.permutation_test test.basic.permutation_test)
