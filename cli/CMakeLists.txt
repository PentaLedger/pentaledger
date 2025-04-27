add_executable(pentaledger_cli
    src/main.cpp
)

target_link_libraries(pentaledger_cli
    PRIVATE
        pentaledger_lib
)

# Install rules
install(TARGETS pentaledger_cli
    RUNTIME DESTINATION bin
) 