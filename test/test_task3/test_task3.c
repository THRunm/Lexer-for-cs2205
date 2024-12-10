// test/test_task3/test_task3.c
#include "test_task3.h"
#include <assert.h>

void build_test_input_task3(int test_case, int* n, struct finite_automata** nfa, int* dst, int* dst_number){}

void build_expected_output_task3(int test_case, int* ans_dst){}

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
    //这个比较逻辑是不对的，可能需要测试者继续补充。
}

int main() {
    for(int i = 1; i <= 10; i++) {
        printf("Test case %d\n", i);
        test_nfa_to_dfa(i);
    }
    return 0;
}
