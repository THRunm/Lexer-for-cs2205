// test/test_task2/test_task2.h
#ifndef TEST_TASK2_H
#define TEST_TASK2_H

#include "../../RegexToNFA.h"
#include "../compare_struct.h"

// Function to build test input
struct simpl_regexp* build_test_input_task2(int test_case, int* src, int* dst);

// Function to build expected output
struct finite_automata* build_expected_output_task2(int test_case);

#endif