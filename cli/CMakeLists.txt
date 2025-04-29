add_executable(pentaledger_cli
    src/main.cpp
)

target_link_libraries(pentaledger_cli
    PRIVATE
        pentaledger_lib
        CLI11::CLI11
)

# Install rules
install(TARGETS pentaledger_cli
    RUNTIME DESTINATION bin
) 