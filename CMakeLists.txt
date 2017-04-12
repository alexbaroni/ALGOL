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

#set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/clang.exe)
#set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/clang++.exe)

project(ALGOL CXX)
enable_testing()

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(include ${Boost_INCLUDE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fconcepts -ftemplate-backtrace-limit=0")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -stdlib=libstdc++ -ftemplate-backtrace-limit=0")
endif()

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Werror -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-inline -g3 -fstack-protector-all")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g0 -DNDEBUG")

add_subdirectory(examples)
add_subdirectory(tests)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
