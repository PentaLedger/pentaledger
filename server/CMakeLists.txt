cmake_minimum_required(VERSION 3.15)
project(pentaledger_server)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check compiler
if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.0")
            message(FATAL_ERROR "Clang version must be at least 10.0 for C++20 support")
        endif()
    endif()
endif()

# Find required packages
find_package(Drogon REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(OpenSSL REQUIRED)

# Add the shared library
add_subdirectory(../lib lib)

# Add source files
set(SERVER_SOURCES
    src/main.cpp
    src/pentaledger_server.cpp
)

# Add include directories
include_directories(
    include
    ../lib/include
)

# Create executable
add_executable(pentaledger_server ${SERVER_SOURCES})

# Link libraries
target_link_libraries(pentaledger_server
    PRIVATE
    pentaledger
    Drogon::Drogon
    JsonCpp::JsonCpp
    OpenSSL::SSL
    OpenSSL::Crypto
    c++fs  # Use c++fs instead of stdc++fs for libc++
)

# Install targets
install(TARGETS pentaledger_server
    RUNTIME DESTINATION bin
)

# Install configuration file
install(FILES config.json
    DESTINATION etc/pentaledger
) 