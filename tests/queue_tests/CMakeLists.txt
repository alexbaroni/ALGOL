# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/ds/queue/concepts.hpp
    ../../include/algol/ds/queue/queue.hpp
    ../../include/algol/ds/queue/fixed_queue.hpp
    ../../include/algol/ds/queue/linked_queue.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(test.queue.array_queue_test ../queue_tests/array_queue_test.cpp)
add_executable(test.queue.fixed_queue_test ../queue_tests/fixed_queue_test.cpp)
add_executable(test.queue.linked_queue_test ../queue_tests/linked_queue_test.cpp)

add_executable(test.queue.all_test ${SOURCE_FILES}
#    ../queue_tests/array_queue_test.cpp
     ../queue_tests/fixed_queue_test.cpp
     ../queue_tests/linked_queue_test.cpp)

#target_link_libraries(test.queue.array_queue_test gtest gtest_main)
target_link_libraries(test.queue.fixed_queue_test gtest gtest_main)
target_link_libraries(test.queue.linked_queue_test gtest gtest_main)
target_link_libraries(test.queue.all_test gtest gtest_main)

#add_test(test.queue.array_queue_test test.queue.array_queue_test)
add_test(test.queue.fixed_queue_test test.queue.fixed_queue_test)
add_test(test.queue.linked_queue_test test.queue.linked_queue_test)
add_test(test.queue.all_test test.queue.all_test)
