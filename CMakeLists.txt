cmake_minimum_required(VERSION 3.29)
project(Grammar_parser_for_cs2205 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Grammar_parser_for_cs2205
        DFALexicalAnalyzer.c
        DFALexicalAnalyzer.h
        main.c
        NFAToDFA.c
        NFAToDFA.h
        RegexToNFA.c
        RegexToNFA.h
        SimplifyRegex.c
        SimplifyRegex.h)
