cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(mlhist ${SOURCE_FILES})

target_link_libraries(mlhist curl)
target_compile_features(mlhist PRIVATE cxx_range_for)

install (TARGETS mlhist DESTINATION bin)
