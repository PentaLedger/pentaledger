cmake_minimum_required(VERSION 3.15)
project(pentaledger_desktop)

# Find wxWidgets package
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
target_link_libraries(pentaledger_desktop ${wxWidgets_LIBRARIES})

# Include directories
target_include_directories(pentaledger_desktop PRIVATE include)

# Install targets
install(TARGETS pentaledger_desktop
    RUNTIME DESTINATION bin
) 