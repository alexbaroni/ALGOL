# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/ds/array/array.hpp
    ../../include/algol/ds/list/list.hpp
    ../../include/algol/ds/stack/fixed_stack.hpp
    ../../include/algol/ds/stack/linked_stack.hpp
    ../../include/algol/ds/stack/stack.hpp
    ../../include/algol/eval/eval.hpp
    ../../include/algol/eval/eval_tokenizer.hpp
    ../../include/algol/func/function.hpp
    ../../include/algol/integer/integer_interval.hpp
    ../../include/algol/integer/integer_interval_range.hpp
    ../../include/algol/io/pprint.hpp
    ../../include/algol/math/math.hpp
    ../../include/algol/perf/operation_counter.hpp
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
    ../../include/algol/result/to.hpp ../../include/algol/perf/benchmark.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.array_test array_test.cpp)
add_executable(test.stopwatch_test stopwatch_test.cpp)
add_executable(test.pprint_test pprint_test.cpp)
add_executable(test.operation_counter_test operation_counter_test.cpp)
add_executable(test.function_test function_test.cpp)
add_executable(test.math_test math_test.cpp)
add_executable(test.integer_interval_test integer_interval_test.cpp)
add_executable(test.integer_interval_range_test integer_interval_range_test.cpp)
add_executable(test.istream_range_test istream_range_test.cpp)
add_executable(test.lines_range_test lines_range_test.cpp)
add_executable(test.sequence_test sequence_test.cpp)
add_executable(test.fibonacci_generator_test fibonacci_generator_test.cpp)
add_executable(test.iota_generator_test iota_generator_test.cpp)
add_executable(test.collatz_generator_test collatz_generator_test.cpp)
add_executable(test.arithmetic_progression_generator_test arithmetic_progression_generator_test.cpp)
add_executable(test.geometric_progression_generator_test geometric_progression_generator_test.cpp)
add_executable(test.factorial_generator_test factorial_generator_test.cpp)
add_executable(test.linked_stack_test linked_stack_test.cpp)
add_executable(test.fixed_stack_test fixed_stack_test.cpp)
add_executable(test.result_test result_test.cpp)
add_executable(test.to_test to_test.cpp)

add_executable(test.all_test ${SOURCE_FILES} array_test.cpp stopwatch_test.cpp pprint_test.cpp
    operation_counter_test.cpp function_test.cpp integer_interval_test.cpp integer_interval_range_test.cpp
    istream_range_test.cpp lines_range_test.cpp sequence_test.cpp fibonacci_generator_test.cpp
    iota_generator_test.cpp math_test.cpp collatz_generator_test.cpp arithmetic_progression_generator_test.cpp
    geometric_progression_generator_test.cpp factorial_generator_test.cpp linked_stack_test.cpp
    fixed_stack_test.cpp result_test.cpp to_test.cpp)

target_link_libraries(test.array_test gtest gtest_main)
target_link_libraries(test.stopwatch_test gtest gtest_main)
target_link_libraries(test.pprint_test gtest gtest_main)
target_link_libraries(test.operation_counter_test gtest gtest_main)
target_link_libraries(test.function_test gtest gtest_main)
target_link_libraries(test.math_test gtest gtest_main)
target_link_libraries(test.integer_interval_test gtest gtest_main)
target_link_libraries(test.integer_interval_range_test gtest gtest_main)
target_link_libraries(test.istream_range_test gtest gtest_main)
target_link_libraries(test.lines_range_test gtest gtest_main)
target_link_libraries(test.sequence_test gtest gtest_main)
target_link_libraries(test.fibonacci_generator_test gtest gtest_main)
target_link_libraries(test.iota_generator_test gtest gtest_main)
target_link_libraries(test.collatz_generator_test gtest gtest_main)
target_link_libraries(test.arithmetic_progression_generator_test gtest gtest_main)
target_link_libraries(test.geometric_progression_generator_test gtest gtest_main)
target_link_libraries(test.factorial_generator_test gtest gtest_main)
target_link_libraries(test.linked_stack_test gtest gtest_main)
target_link_libraries(test.fixed_stack_test gtest gtest_main)
target_link_libraries(test.result_test gtest gtest_main)
target_link_libraries(test.to_test gtest gtest_main)

target_link_libraries(test.all_test gtest gtest_main)

add_test(array_test test.array_test)
add_test(stopwatch_test test.stopwatch_test)
add_test(pprint_test test.pprint_test)
add_test(operation_counter_test test.operation_counter_test)
add_test(function_test test.function_test)
add_test(math_test test.math_test)
add_test(integer_interval_test test.integer_interval_test)
add_test(integer_interval_range_test test.integer_interval_range_test)
add_test(istream_range_test test.istream_range_test)
add_test(lines_range_test test.lines_range_test)
add_test(sequence_test test.sequence_test)
add_test(fibonacci_generator_test test.fibonacci_generator_test)
add_test(iota_generator_test test.iota_generator_test)
add_test(collatz_generator_test test.collatz_generator_test)
add_test(arithmetic_progression_generator_test test.arithmetic_progression_generator_test)
add_test(geometric_progression_generator_test test.geometric_progression_generator_test)
add_test(factorial_generator_test test.factorial_generator_test)
add_test(linked_stack_test test.linked_stack_test)
add_test(fixed_stack_test test.fixed_stack_test)
add_test(result_test test.result_test)
add_test(to_test test.to_test)
