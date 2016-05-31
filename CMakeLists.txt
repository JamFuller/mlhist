cmake_minimum_required(VERSION 2.8.7)

# TODO(jim.fuller@webcomposite.com): add travis builds to generate releases for linux/osx/windows.

project(mlhist)

include_directories(mlhist)
add_subdirectory(mlhist)

add_subdirectory(mlhist_tests)