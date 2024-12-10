cmake_minimum_required(VERSION 3.16)
project(Grammar_parser_for_cs2205 C)

set(CMAKE_C_STANDARD 11)

# Include current directory
include_directories(.)

# Enable testing
enable_testing()

# Add source files
set(SOURCE_FILES
    lang.c
    compare_struct.c
    SimplifyRegex.c
    RegexToNFA.c
    NFAToDFA.c
    DFALexicalAnalyzer.c
)

# Create main library
add_library(regex_parser ${SOURCE_FILES})

# Add test directories
add_subdirectory(test/test_task1)
add_subdirectory(test/test_task2)
add_subdirectory(test/test_task3)
add_subdirectory(test/test_task4)