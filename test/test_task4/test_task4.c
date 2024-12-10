// test/test_task4/test_task4.c
#include "test_task4.h"
#include <assert.h>
#include <string.h>

void build_test_input_task4(int test_case, struct finite_automata** dfa, int** types, 
                           struct type** type, int* types_num, char** input){}

struct tokens* build_expected_output_task4(int test_case){ 
    
}

bool compare_tokens(struct tokens* t1, struct tokens* t2) {
    if (t1->n != t2->n) return 0;
    
    for (int i = 0; i < t1->n; i++) {
        if (strcmp(t1->tokens[i].value, t2->tokens[i].value) != 0) return 0;
        if (t1->tokens[i].type->id != t2->tokens[i].type->id) return 0;
        if (strcmp(t1->tokens[i].type->name, t2->tokens[i].type->name) != 0) return 0;
    }
    return 1;
}

void test_lexical_analyzer(int test_case) {
    struct finite_automata* dfa;
    int* types;
    struct type* type;
    int types_num;
    char* input;
    
    // Build input
    build_test_input_task4(test_case, &dfa, &types, &type, &types_num, &input);
    
    // Build expected output
    struct tokens* expected = build_expected_output_task4(test_case);
    
    // Get actual output
    struct tokens actual = tokenize(dfa, types, type, types_num, input);
    
    // Compare results
    assert(compare_tokens(&actual, expected) && "Tokens don't match expected output");
}

int main() {
    for(int i = 1; i <= 10; i++) {
        printf("Test case %d\n", i);
        test_lexical_analyzer(i);
    }
    return 0;
}