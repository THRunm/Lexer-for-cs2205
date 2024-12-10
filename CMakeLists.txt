cmake_minimum_required(VERSION 3.16)
project(Grammar_parser_for_cs2205 C)

set(CMAKE_C_STANDARD 11)

# Include current directory
include_directories(.)

# Create executable with all source files
add_executable(Grammar_parser_for_cs2205
    main.c
    lang.c
    compare_struct.c
    DFALexicalAnalyzer.c
    NFAToDFA.c
    RegexToNFA.c
    SimplifyRegex.c
)