add_executable(linear_search linear_search.cpp)
add_executable(kth-largest kth-largest.cpp)
add_executable(collatz_seq collatz_seq.cpp)
add_executable(collatz_seq_2 collatz_seq_2.cpp)
add_executable(project_euler_002 project_euler_002.cpp)
add_executable(stack.array_reverse stack/array_reverse.cpp)
add_executable(stack.balanced_delimitiers stack/balanced_delimitiers.cpp)
add_executable(stack.evaluate_postfix stack/evaluate_postfix.cpp)

add_custom_target(examples DEPENDS linear_search kth-largest collatz_seq collatz_seq_2 project_euler_002
    stack.array_reverse stack.balanced_delimitiers stack.evaluate_postfix)