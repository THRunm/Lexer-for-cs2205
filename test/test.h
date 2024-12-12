//
// Created by asus on 24-12-10.
//

#ifndef TEST_H
#define TEST_H

#include "../include/DFALexicalAnalyzer.h"
#include "../include/lang.h"

extern int number_of_test;

extern struct type * test_types;

extern struct frontend_regexp ** test_fr;

void initialize_test_types(int test_case);

void allocate_and_initialize_test_fr(int test_case);

#endif //TEST_H
