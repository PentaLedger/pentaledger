cmake_minimum_required(VERSION 3.10)
project(PentaLedger VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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