# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/algorithms/sort/bogo_sort.hpp
    ../../include/algol/algorithms/sort/bubble_sort.hpp
    ../../include/algol/algorithms/sort/selection_sort.hpp
    ../../include/algol/algorithms/sort/insertion_sort.hpp
    ../../include/algol/algorithms/sort/shell_sort.hpp
    ../../include/algol/sequence/generator/halving_generator.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.sort.bogo_sort_test bogo_sort_test.cpp)
add_executable(test.sort.bubble_sort_test bubble_sort_test.cpp)
add_executable(test.sort.selection_sort_test selection_sort_test.cpp)
add_executable(test.sort.insertion_sort_test insertion_sort_test.cpp)
add_executable(test.sort.shell_sort_test shell_sort_test.cpp)

add_executable(test.sort.all_test ${SOURCE_FILES}
    bogo_sort_test.cpp
    bubble_sort_test.cpp
    selection_sort_test.cpp
    insertion_sort_test.cpp
    shell_sort_test.cpp)

target_link_libraries(test.sort.bogo_sort_test ${Boost_LIBRARIES} gtest gtest_main)
target_link_libraries(test.sort.bubble_sort_test gtest gtest_main)
target_link_libraries(test.sort.selection_sort_test gtest gtest_main)
target_link_libraries(test.sort.insertion_sort_test gtest gtest_main)
target_link_libraries(test.sort.shell_sort_test gtest gtest_main)
target_link_libraries(test.sort.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.sort.bogo_sort_test test.sort.bogo_sort_test)
add_test(test.sort.bubble_sort_test test.sort.bubble_sort_test)
add_test(test.sort.selection_sort_test test.sort.selection_sort_test)
add_test(test.sort.insertion_sort_test test.sort.insertion_sort_test)
add_test(test.sort.shell_sort_test test.sort.shell_sort_test)
add_test(test.sort.all_test test.sort.all_test)
