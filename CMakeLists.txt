cmake_minimum_required(VERSION 3.17)
project(TSP_1)

set(CMAKE_CXX_STANDARD 20)
#add_compile_options(-Wall -Wextra -Werror)
set(SOURCE_FILES
        src/TSP.cpp
        src/tsp_setup.cpp
        )

add_executable(TSP ${SOURCE_FILES} main.cpp )
include_directories(include)

set(SOURCES_FILES_TEST
        test/main_gtest.cpp
        test/tsp_test.cpp)

add_executable(TSP_test ${SOURCE_FILES} ${SOURCES_FILES_TEST} test/main_gtest.cpp)
target_include_directories(TSP_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        )
add_subdirectory(googletest-master googletest-master)
target_link_libraries(TSP_test gmock)