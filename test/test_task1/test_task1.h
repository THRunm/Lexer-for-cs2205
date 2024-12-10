// test/test_task1/test_task1.h
#ifndef TEST_TASK1_H
#define TEST_TASK1_H

#include "../../SimplifyRegex.h"
#include "../compare_struct.h"

// Function to build test input
struct frontend_regexp* build_test_input_task1(int test_case);

// Function to build expected output
struct simpl_regexp* build_expected_output_task1(int test_case);

#endif