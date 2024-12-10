//
// Created by asus on 24-12-10.
//

#ifndef TEST_H
#define TEST_H

#include "../include/DFALexicalAnalyzer.h"
#include "../include/lang.h"

extern int number_of_test1;

extern struct type * test_types_1;

extern struct frontend_regexp ** test_fr_1;

void initialize_test1_types();

void allocate_and_initialize_test_fr_1();

#endif //TEST_H
