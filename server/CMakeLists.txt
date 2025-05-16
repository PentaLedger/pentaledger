cmake_minimum_required(VERSION 3.15)
project(pentaledger_server)

# Set C++ standard and compiler flags for macOS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# Find required packages
find_package(Drogon REQUIRED)
find_package(OpenSSL REQUIRED)

# Find JsonCpp
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

# Add the shared library
#add_subdirectory(../lib lib)

# Add source files
set(SERVER_SOURCES
    src/main.cpp
    src/pentaledger_server.cpp
)

# Add include directories
include_directories(
    include
    ../lib/include
    ${JSONCPP_INCLUDE_DIRS}
)

# Create executable
add_executable(pentaledger_server ${SERVER_SOURCES})

# Link libraries
target_link_libraries(pentaledger_server
    PRIVATE
#    pentaledger
    Drogon::Drogon
    ${JSONCPP_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Set RPATH for macOS
if(APPLE)
    set_target_properties(pentaledger_server PROPERTIES
        INSTALL_RPATH "@executable_path"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

# Install targets
install(TARGETS pentaledger_server
    RUNTIME DESTINATION bin
)

# Install configuration file
install(FILES config.json
    DESTINATION etc/pentaledger
) 