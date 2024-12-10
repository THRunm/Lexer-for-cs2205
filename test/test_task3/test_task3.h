// test/test_task3/test_task3.h
#ifndef TEST_TASK3_H
#define TEST_TASK3_H

#include "../../NFAToDFA.h"
#include "../compare_struct.h"

// Function to build test input
void build_test_input_task3(int test_case, int* n, struct finite_automata** nfa, int* dst, int* dst_number);

// Function to build expected output
void build_expected_output_task3(int test_case, int* ans_dst);

#endif