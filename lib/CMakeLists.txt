add_library(pentaledger_lib
    src/pentaledger.cpp
    src/db/database.cpp
    src/utility/wordwrap.cpp
    src/converter/ASCII_to_EBCDIC.cpp
    include/pentaledger/pentaledger.hpp
    include/pentaledger/db/database.hpp
    include/pentaledger/utility/wordwrap.h
    include/pentaledger/converter/ASCII_to_EBCDIC.hpp
)

target_include_directories(pentaledger_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(pentaledger_lib
    PRIVATE
        ${PostgreSQL_LIBRARIES}
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