cmake_minimum_required(VERSION 3.2.2)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_subdirectory(lib/googletest-master)

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${GMOCK_INCLUDE_DIRS})

set(UNIT_TESTS runUnitTests)

add_executable(${UNIT_TESTS} test_history.cpp)

# standard linking to gtest stuff
target_link_libraries(${UNIT_TESTS} gtest gmock gtest_main pthread curl)

# This is so you can do 'make test' to see all your tests run, instead of manually running the executable runUnitTests to see those specific tests.
add_test(NAME mlUnitTests COMMAND runUnitTests)
