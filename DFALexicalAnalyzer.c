//
// Created by asus on 24-11-20.
//

#include "lang.h"
#include <string.h>
#include "DFALexicalAnalyzer.h"

// Function to free the tokens
void free_tokens(struct tokens *tokens) {
    for (int i = 0; i < tokens->n; i++) {
        free(tokens->tokens[i].value);
    }
    free(tokens->tokens);
    free(tokens);
}

// Function to free the DFA
void free_dfa(struct _finite_automata *dfa) {
    for (int i = 0; i < dfa->n; i++) {
        free(dfa->next_state[i]);
    }
    free(dfa->next_state);
    free(dfa->src);
    free(dfa->dst);
    free(dfa->lb);
    for (int i = 0; i < dfa->n; i++) {
        if (dfa->accepting_token_type[i] != NULL)
        free(dfa->accepting_token_type[i]);
    }
    free(dfa);
}


// Function to build the next_state transition table
struct _finite_automata * build_next_state(struct finite_automata *dfa,const int * types,struct type* type,int types_num) {
    struct _finite_automata *dfa_ = malloc(sizeof(struct _finite_automata));
    dfa_->n = dfa->n;
    dfa_->m = dfa->m;
    dfa_->src = dfa->src;
    dfa_->dst = dfa->dst;
    dfa_->lb = dfa->lb;
    dfa_->accepting_token_type = malloc(sizeof(struct type *) * dfa->n);
    for (int i = 0; i < dfa->n; i++) {
        dfa_->accepting_token_type[i] = NULL;
    }
    for (int i = 0; i < types_num; i++) {
        dfa_->accepting_token_type[types[i]] = &type[i];
    }
    int i, e, s;
    dfa_->next_state = malloc(sizeof(int *) * dfa->n);
    for (s = 0; s < dfa->n; s++) {
        dfa_->next_state[s] = malloc(sizeof(int) * 256);
        for (i = 0; i < 256; i++) {
            dfa_->next_state[s][i] = -1;
        }
    }

    for (e = 0; e < dfa->m; e++) {
        int src = dfa->src[e];
        int dst = dfa->dst[e];
        struct char_set *cs = &(dfa->lb[e]);

        if (cs->n == 0) {
            fprintf(stderr, "Warning: Epsilon transition found in DFA.\n");
            continue;
        }
        else {
            for (unsigned int j = 0; j < cs->n; j++) {
                unsigned char c = (unsigned char) cs->c[j];
                if (dfa_->next_state[src][c] != -1) {
                    fprintf(stderr, "Error: Non-deterministic transition found in DFA at state %d with input '%c'.\n", src, c);
                    exit(1);
                }
                dfa_->next_state[src][c] = dst;
            }
        }
    }
}

// Function to perform lexical analysis using the DFA
struct tokens tokenize(struct finite_automata *intput_dfa,int * types,struct type *type, int types_num, const char *input){
    struct _finite_automata *dfa = build_next_state(intput_dfa,types,type,types_num);
    int position = 0;
    struct tokens result;
    result.tokens = malloc(sizeof(struct token) * 16);
    result.n = 0;
    int capacity = 16;
    int input_length = strlen(input);
    while (position < input_length) {
        int current_state = 0;
        int last_accepting_state = -1;
        int last_accepting_position = -1;
        int i = position;

        while (i < input_length) {
            unsigned char c = (unsigned char) input[i];
            int next_state = dfa->next_state[current_state][c];
            if (next_state == -1) {
                break;
            }
            current_state = next_state;
            if (dfa->accepting_token_type[current_state] != NULL) {
                last_accepting_state = current_state;
                last_accepting_position = i + 1;
            }
            i++;
        }

        if (last_accepting_state == -1) {
            fprintf(stderr, "Error: No viable token found at position %d.\n", position);
            exit(1);
        } else {
            int token_length = last_accepting_position - position;
            char *token = (char *) malloc(token_length + 1);
            memcpy(token, input + position, token_length);
            token[token_length] = '\0';
            struct type* token_type = dfa->accepting_token_type[last_accepting_state];
            struct token t;
            t.value = token;
            t.type = token_type;
            result.tokens[result.n] = t;
            result.n++;
            if (result.n == capacity) {
                capacity *= 2;
                struct token *new_tokens = malloc(sizeof(struct token) * capacity);
                memcpy(new_tokens, result.tokens, sizeof(struct token) * result.n);
                for (int i = 0; i < result.n; i++) {
                    free(result.tokens[i].value);
                }
                free(result.tokens);
                result.tokens = new_tokens;
            }
            position = last_accepting_position;
        }
    }
    return result;
}

void print(struct tokens *tokens) {
    for (int i = 0; i < tokens->n; i++) {
        printf("Token: %s, Type: %s\n", tokens->tokens[i].value, tokens->tokens[i].type->name);
    }
}