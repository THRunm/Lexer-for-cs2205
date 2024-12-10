// test/test_task1/test_task1.c
#include "test_task1.h"
#include <assert.h>

void test_simplify_regex(int test_case) {
    // Build input
    struct frontend_regexp* input = build_test_input_task1(test_case);
    
    // Build expected output
    struct simpl_regexp* expected = build_expected_output_task1(test_case);
    
    // Get actual output
    struct simpl_regexp* actual = transform_to_simplified(input);
    
    // Compare results
    assert(compare_simpl_regexp(expected, actual) && "Simplified regex doesn't match expected output");
}

int main() {
    // Run tests for different test cases
    for(int i = 1; i <= 10; i++) {
        test_simplify_regex(i);
    }
    return 0;
}
