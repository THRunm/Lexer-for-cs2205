// test/test_task2/test_task2.c
#include "test_task2.h"
#include <assert.h>

void test_build_nfa(int test_case) {
    int src, dst;
    
    // Build input
    struct simpl_regexp* input = build_test_input_task2(test_case, &src, &dst);
    
    // Build expected output
    struct finite_automata* expected = build_expected_output_task2(test_case);
    
    // Get actual output
    struct finite_automata* actual = build_nfa(input, &src, &dst);
    
    // Compare results
    assert(compare_finite_automata(expected, actual) && "NFA doesn't match expected output");
}

int main() {
    for(int i = 1; i <= 10; i++) {
        test_build_nfa(i);
    }
    return 0;
}
