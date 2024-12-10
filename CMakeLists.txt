# Root CMakeLists.txt
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

# test/test_task1/CMakeLists.txt
add_executable(test_task1 test_task1.c)
target_link_libraries(test_task1 regex_parser)
add_test(NAME SimplifyRegex COMMAND test_task1)

# test/test_task2/CMakeLists.txt
add_executable(test_task2 test_task2.c)
target_link_libraries(test_task2 regex_parser)
add_test(NAME RegexToNFA COMMAND test_task2)

# test/test_task3/CMakeLists.txt
add_executable(test_task3 test_task3.c)
target_link_libraries(test_task3 regex_parser)
add_test(NAME NFAToDFA COMMAND test_task3)

# test/test_task4/CMakeLists.txt
add_executable(test_task4 test_task4.c)
target_link_libraries(test_task4 regex_parser)
add_test(NAME DFALexicalAnalyzer COMMAND test_task4)