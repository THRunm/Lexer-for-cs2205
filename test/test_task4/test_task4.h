// test/test_task4/test_task4.h
#ifndef TEST_TASK4_H
#define TEST_TASK4_H

#include "../../DFALexicalAnalyzer.h"
#include "../compare_struct.h"

// Function to build test input
void build_test_input_task4(int test_case, struct finite_automata** dfa, int** types, 
                           struct type** type, int* types_num, char** input);

// Function to build expected output
struct tokens* build_expected_output_task4(int test_case);

#endif