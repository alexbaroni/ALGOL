add_executable(linear_search linear_search.cpp)
add_executable(kth-largest kth-largest.cpp)
add_executable(collatz_seq collatz_seq.cpp)
add_executable(collatz_seq_2 collatz_seq_2.cpp)
add_executable(project_euler_002 project_euler_002.cpp)
add_executable(benchmark benchmark.cpp)
add_executable(stack.array_reverse stack/array_reverse.cpp)
add_executable(stack.constexpr stack/constexpr.cpp)
add_executable(stack.balanced_delimitiers stack/balanced_delimitiers.cpp)
add_executable(stack.evaluate_postfix stack/evaluate_postfix.cpp)
add_executable(stack.prefix_to_postfix stack/prefix_to_postfix.cpp)
add_executable(stack.postfix_to_prefix stack/postfix_to_prefix.cpp)
add_executable(stack.sort stack/sort.cpp)
add_executable(recursion.factorial recursion/factorial.cpp utility/utility.hpp)
add_executable(recursion.prod_first_n recursion/prod_first_n.cpp)
add_executable(recursion.max recursion/max.cpp)
add_executable(recursion.tower_of_hanoi recursion/tower_of_hanoi.cpp)

add_custom_target(examples DEPENDS linear_search kth-largest collatz_seq collatz_seq_2
    project_euler_002 benchmark
    stack.array_reverse stack.constexpr stack.balanced_delimitiers stack.evaluate_postfix
    stack.prefix_to_postfix stack.postfix_to_prefix stack.sort recursion.factorial recursion.prod_first_n
    recursion.max recursion.tower_of_hanoi)