# Include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add testing library
add_library(overseer_tests STATIC
    test_main.cpp
)

# Link testing library with Google Test
target_link_libraries(overseer_tests gtest gtest_main)

# Add test target
add_executable(overseer_test_main test_main.cpp)

# Link test target with testing library and the project executable
target_link_libraries(overseer_test_main overseer_tests gtest gtest_main)

# Add test
add_test(NAME overseer_test COMMAND overseer_test_main)