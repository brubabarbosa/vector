cmake_minimum_required(VERSION 3.5)
project (Vector)

#=== SETTING VARIABLES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 11)
set( GCC_COMPILE_FLAGS "-Wall -pthread" )
set( PREPROCESSING_FLAGS  "-D PRINT")
#set( PREPROCESSING_FLAGS  "-D PRINT -D DEBUG -D CASE="WORST" -D ALGO="QUAD"')
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include )

add_executable(run_tests "src/main.cpp")

# Link with the google test libraries.
target_link_libraries(run_tests ${GTEST_LIBRARIES})

#define C++11 as the standard.
#set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)
#target_compile_features(run_tests PUBLIC cxx_std_11)
