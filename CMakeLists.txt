# algol - A algorithm analysis utility library
#
#  Copyright Alessandro Baroni 2017
#
#  Use, modification and distribution is subject to the
#  Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
# Project home: https://github.com/alexbaroni/ALGOL
#
#
cmake_minimum_required(VERSION 3.6)

project(ALGOL CXX)

include_directories(include)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fconcepts -ftemplate-backtrace-limit=0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -march=native")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-inline -g3 -fstack-protector-all")
  set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g0 -DNDEBUG")
endif()

add_subdirectory(examples)
add_subdirectory(tests)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
