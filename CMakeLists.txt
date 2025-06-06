cmake_minimum_required(VERSION 3.10)
project(PentaLedger VERSION 0.0.1 LANGUAGES CXX)

# Enable testing
enable_testing()

# Set C++ standard and features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# turn off deprecated warnings in gtest, etc.
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# Include FetchContent
include(FetchContent)

# Fetch CLI11
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.1
)
FetchContent_MakeAvailable(CLI11)

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Add option for building documentation
option(BUILD_DOCS "Build Doxygen documentation" ON)

# Find Doxygen if documentation is enabled
if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    # Configure Doxygen
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   @ONLY)

    # Add documentation target
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(tests) 
#add_subdirectory(server)
