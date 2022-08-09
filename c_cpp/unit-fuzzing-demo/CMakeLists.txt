cmake_minimum_required(VERSION 3.16)
project(cmake_example)

enable_testing()

find_package(cifuzz)
enable_fuzz_testing()

add_subdirectory(src)
add_subdirectory(fuzz_tests)
add_subdirectory(unit_tests)

add_executable(${PROJECT_NAME} main.cpp )
target_link_libraries(${PROJECT_NAME} PRIVATE exploreMe)

# Unit Test Code
add_executable(my_ctest unit_tests/my_ctest.cpp)
target_link_libraries(my_ctest PRIVATE exploreMe)

# define tests
add_test(
  NAME my_ctest
  COMMAND $<TARGET_FILE:my_ctest>
)

add_fuzz_test(my_fuzz_test fuzz_tests/my_fuzz_test.cpp)
target_link_libraries(my_fuzz_test PRIVATE exploreMe)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(my_gtest unit_tests/my_gtest.cpp)
target_link_libraries(my_gtest exploreMe GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_gtest)
