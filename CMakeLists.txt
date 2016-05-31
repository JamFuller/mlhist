cmake_minimum_required(VERSION 3.2.2)

# TODO(jim.fuller@webcomposite.com): add travis builds to generate releases for linux/osx/windows.

project(mlhist)

include_directories(mlhist)
add_subdirectory(mlhist)

add_subdirectory(mlhist_tests)

enable_testing ()
add_test (NAME test COMMAND runUnitTests)
