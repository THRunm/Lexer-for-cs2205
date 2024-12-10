// test/test_task3/test_task3.c
#include "test_task3.h"
#include <assert.h>

void test_nfa_to_dfa(int test_case) {
    int n;
    struct finite_automata* nfa;
    int dst, dst_number;
    int expected_ans_dst;
    
    // Build input
    build_test_input_task3(test_case, &n, &nfa, &dst, &dst_number);
    
    // Build expected output
    build_expected_output_task3(test_case, &expected_ans_dst);
    
    // Get actual output
    int actual_ans_dst;
    NFA2DFA(n, &nfa, &dst, &dst_number, &actual_ans_dst);
    
    // Compare results
    assert(actual_ans_dst == expected_ans_dst && "DFA doesn't match expected output");
}

int main() {
    for(int i = 1; i <= 5; i++) {
        test_nfa_to_dfa(i);
    }
    return 0;
}
