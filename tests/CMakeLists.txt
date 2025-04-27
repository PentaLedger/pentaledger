# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(pentaledger_tests
    src/pentaledger_tests.cpp
    src/date/leap_year_test.cpp
    src/transportation/fuel_efficiency_test.cpp
    src/utility/Environment_test.cpp
    src/utility/wordwrap_test.cpp
)

# Link test executable with Google Test and our library
target_link_libraries(pentaledger_tests
    PRIVATE
        pentaledger_lib
        GTest::gtest_main
)

# Add test to CTest
add_test(NAME pentaledger_tests COMMAND pentaledger_tests) 