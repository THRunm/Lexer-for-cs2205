#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/DFALexicalAnalyzer.h"
#include "../include/NFAToDFA.h"
#include "../include/RegexToNFA.h"
#include "../include/SimplifyRegex.h"
#include "../test/test.h"

void read_inputs(char *file_name, char ***inputs, int *number) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        *number = 0;
        *inputs = NULL;
        return;
    }
    size_t capacity = 10;
    size_t count = 0;
    char **array = malloc(capacity * sizeof(char *));
    if (array == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        *number = 0;
        *inputs = NULL;
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        if (count >= capacity) {
            capacity *= 2;
            char **new_array = realloc(array, capacity * sizeof(char *));
            if (new_array == NULL) {
                perror("Failed to reallocate memory");
                for (size_t i = 0; i < count; i++) {
                    free(array[i]);
                }
                free(array);
                fclose(fp);
                *number = 0;
                *inputs = NULL;
                return;
            }
            array = new_array;
        }
        array[count] = malloc((len + 1) * sizeof(char));
        if (array[count] == NULL) {
            perror("Failed to allocate memory for line");
            for (size_t i = 0; i < count; i++) {
                free(array[i]);
            }
            free(array);
            fclose(fp);
            *number = 0;
            *inputs = NULL;
            return;
        }
        strcpy(array[count], buffer);
        count++;
    }
    fclose(fp);
    *inputs = array;
    *number = (int) count;
}



int main(int argc, char *argv[]) {
    initialize_test1_types();
    allocate_and_initialize_test_fr_1();
    int test_case =atoi(argv[1]);
    struct frontend_regexp **fr_regexps ;
    struct type *types;
    int types_num;
    char **inputs;
    int number;
    read_inputs(argv[2], &inputs, &number);
    switch (test_case)
    {
        case 1: {
            fr_regexps=test_fr_1;
            types=test_types_1;
            types_num=number_of_test1;
        }
    }
    struct simpl_regexp **sr_regexps = (struct simpl_regexp **)malloc(types_num * sizeof(struct simpl_regexp *));
    for (int i = 0; i < types_num; i++) {
        print_frontend_regexp(fr_regexps[i]);
        sr_regexps[i] = transform_to_simplified(fr_regexps[i]);
        print_simpl_regexp(sr_regexps[i]);
    }
    struct finite_automata **nfa = (struct finite_automata **)malloc(types_num * sizeof(struct finite_automata *));
    int *start = (int *)malloc(types_num * sizeof(int));
    int *end = (int *)malloc(types_num * sizeof(int));
    for (int i = 0; i < types_num; i++) {
        nfa[i] = build_nfa(sr_regexps[i],start,end);
    }
    print(nfa[0]);
    int dst_number = 0;
    int *dst = (int *)malloc(types_num * sizeof(int));
    
    struct finite_automata dfa = NFA2DFA(types_num, nfa, end, &dst_number, dst);
    print(&dfa);
    for (int i=0;i<number;i++)
    {struct tokens tokens=tokenize(&dfa, dst, types, types_num, inputs[i]);
    printf("Tokens:\n");
    print_token(tokens);
    free_tokens(&tokens);
    }
    free_dfa(&dfa);
    for (int i = 0; i < types_num; i++) {
        free_simpl_regexp(sr_regexps[i]);
        free_frontend_regexp(fr_regexps[i]);
        free(nfa[i]);
    }
    return 0;
}