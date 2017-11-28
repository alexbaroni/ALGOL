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
cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_COMPILER gcc-7.2)
set(CMAKE_CXX_COMPILER g++-7.2)

project(ALGOL CXX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost COMPONENTS coroutine REQUIRED)

include_directories(include ${Boost_INCLUDE_DIR} lib/cmcstl2/include lib/pcg-cpp/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fconcepts -fconstexpr-depth=2048 -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Werror -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-inline -g3 -fno-omit-frame-pointer -fstack-protector-all")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g0 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

if (ENABLE_SAN)
  message(STATUS "ENABLE_SAN")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
endif ()

if (ENABLE_GCOV)
  message(STATUS "ENABLE_GCOV")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

if (ENABLE_GPROF)
  message(STATUS "ENABLE_GPROF")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif ()

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/home/derkalt/toolchains/gcc-7.2.0/lib64")

#add_subdirectory(lib/cmcstl2)
add_subdirectory(examples)
add_subdirectory(tests)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
