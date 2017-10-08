# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/sequence/generator/arithmetic_progression_generator.hpp
    ../../include/algol/sequence/generator/collatz_generator.hpp
    ../../include/algol/sequence/generator/factorial_generator.hpp
    ../../include/algol/sequence/generator/fibonacci_generator.hpp
    ../../include/algol/sequence/generator/geometric_progression_generator.hpp
    ../../include/algol/sequence/generator/iota_generator.hpp
    ../../include/algol/sequence/sequence.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.seq.arithmetic_progression_generator_test arithmetic_progression_generator_test.cpp)
add_executable(test.seq.collatz_generator_test collatz_generator_test.cpp)
add_executable(test.seq.factorial_generator_test factorial_generator_test.cpp)
add_executable(test.seq.fibonacci_generator_test fibonacci_generator_test.cpp)
add_executable(test.seq.geometric_progression_generator_test geometric_progression_generator_test.cpp)
add_executable(test.seq.iota_generator_test iota_generator_test.cpp)
add_executable(test.seq.sequence_test sequence_test.cpp)

add_executable(test.seq.all_test ${SOURCE_FILES}
    arithmetic_progression_generator_test.cpp
    collatz_generator_test.cpp
    factorial_generator_test.cpp
    fibonacci_generator_test.cpp
    geometric_progression_generator_test.cpp
    iota_generator_test.cpp
    sequence_test.cpp)

target_link_libraries(test.seq.arithmetic_progression_generator_test gtest gtest_main)
target_link_libraries(test.seq.collatz_generator_test gtest gtest_main)
target_link_libraries(test.seq.factorial_generator_test gtest gtest_main)
target_link_libraries(test.seq.fibonacci_generator_test gtest gtest_main)
target_link_libraries(test.seq.geometric_progression_generator_test gtest gtest_main)
target_link_libraries(test.seq.iota_generator_test gtest gtest_main)
target_link_libraries(test.seq.sequence_test gtest gtest_main)
target_link_libraries(test.seq.all_test gtest gtest_main)

add_test(test.seq.arithmetic_progression_generator_test test.seq.arithmetic_progression_generator_test)
add_test(test.seq.collatz_generator_test test.seq.collatz_generator_test)
add_test(test.seq.factorial_generator_test test.seq.factorial_generator_test)
add_test(test.seq.fibonacci_generator_test test.seq.fibonacci_generator_test)
add_test(test.seq.geometric_progression_generator_test test.seq.geometric_progression_generator_test)
add_test(test.seq.iota_generator_test test.seq.iota_generator_test)
add_test(test.seq.sequence_test test.seq.sequence_test)
add_test(test.seq.all_test test.seq.all_test)
