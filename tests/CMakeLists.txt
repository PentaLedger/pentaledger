# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(pentaledger_tests
    src/pentaledger_tests.cpp
)

# Link test executable with Google Test and our library
target_link_libraries(pentaledger_tests
    PRIVATE
        pentaledger_lib
        gtest
        gtest_main
)

# Add test to CTest
add_test(NAME pentaledger_tests COMMAND pentaledger_tests) 