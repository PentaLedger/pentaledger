cmake_minimum_required(VERSION 3.15)
project(pentaledger_desktop)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add source files
set(DESKTOP_SOURCES
    src/main.cpp
    src/main_frame.cpp
)

# Add header files
set(DESKTOP_HEADERS
    include/main_frame.h
)

# Create executable
add_executable(pentaledger_desktop ${DESKTOP_SOURCES} ${DESKTOP_HEADERS})

# Link libraries
target_link_libraries(pentaledger_desktop PRIVATE ${wxWidgets_LIBRARIES})

# Include directories
target_include_directories(pentaledger_desktop PRIVATE include)

# Set compiler flags
if(APPLE)
    target_compile_options(pentaledger_desktop PRIVATE -Wall -Wextra)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(pentaledger_desktop PRIVATE -stdlib=libc++)
    endif()
endif()

# Install targets
install(TARGETS pentaledger_desktop
    RUNTIME DESTINATION bin
) 