# hack to make clion see this file belong to the project
set(SOURCE_FILES
    ../../include/algol/result/result.hpp
    ../../include/algol/result/to.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test.result.result_test result_test.cpp)
add_executable(test.result.to_test to_test.cpp)

add_executable(test.result.all_test ${SOURCE_FILES}
    result_test.cpp
    to_test.cpp)

target_link_libraries(test.result.result_test gtest gtest_main)
target_link_libraries(test.result.to_test gtest gtest_main)
target_link_libraries(test.result.all_test ${Boost_LIBRARIES} gtest gtest_main)

add_test(test.result.result_test test.result.result_test)
add_test(test.result.to_test test.result.to_test)
add_test(test.result.all_test test.result.all_test)
