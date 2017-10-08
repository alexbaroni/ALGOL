# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/ds/stack/fixed_stack.hpp
    ../../include/algol/ds/stack/linked_stack.hpp
    ../../include/algol/ds/stack/array_stack.hpp
    ../../include/algol/ds/stack/stack.hpp
    ../../include/algol/ds/stack/concepts.hpp
    ../../include/algol/algorithms/stack/sort.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.stack.array_stack_test ../stack_tests/array_stack_test.cpp)
add_executable(test.stack.fixed_stack_test ../stack_tests/fixed_stack_test.cpp)
add_executable(test.stack.linked_stack_test ../stack_tests/linked_stack_test.cpp)

add_executable(test.stack.all_test ${SOURCE_FILES}
    ../stack_tests/array_stack_test.cpp
    ../stack_tests/fixed_stack_test.cpp
    ../stack_tests/linked_stack_test.cpp)

target_link_libraries(test.stack.array_stack_test gtest gtest_main)
target_link_libraries(test.stack.fixed_stack_test gtest gtest_main)
target_link_libraries(test.stack.linked_stack_test gtest gtest_main)
target_link_libraries(test.stack.all_test gtest gtest_main)

add_test(test.stack.array_stack_test test.stack.array_stack_test)
add_test(test.stack.fixed_stack_test test.stack.fixed_stack_test)
add_test(test.stack.linked_stack_test test.stack.linked_stack_test)
add_test(test.stack.all_test test.stack.all_test)
