add_library(pentaledger_lib
    src/pentaledger.cpp
    include/pentaledger/pentaledger.hpp
)

target_include_directories(pentaledger_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install rules
install(TARGETS pentaledger_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/pentaledger
    DESTINATION include
) 