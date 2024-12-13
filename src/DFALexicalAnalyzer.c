//
// Created by asus on 24-11-20.
//

#include "lang.h"
#include <string.h>
#include "DFALexicalAnalyzer.h"

// Function to free the tokens
void free_tokens(struct tokens *tokens) {
    if (tokens == NULL) return;
    for (int i = 0; i < tokens->n; i++) {
        if (tokens->tokens[i].value != NULL) {
            free(tokens->tokens[i].value);
        }
    }
    free(tokens->tokens);
    tokens->tokens = NULL;
    tokens->n = 0;
}

// Function to free the DFA
void free_dfa(struct _finite_automata *dfa) {
    if (dfa == NULL) return;
    if (dfa->next_state != NULL) {
        for (int s = 0; s < dfa->n; s++) {
            if (dfa->next_state[s] != NULL) {
                free(dfa->next_state[s]);
            }
        }
        free(dfa->next_state);
    }
    if (dfa->accepting_token_type != NULL) {
        free(dfa->accepting_token_type);
    }
    free(dfa);
}


// Function to build the next_state transition table
struct _finite_automata * build_next_state(struct finite_automata *dfa,const int ** types,struct type* type,int types_num,int *count,int *num) {
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
        dfa_->accepting_token_type[types[count[i]][num[i]]] = &type[count[i]];
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
    return dfa_;
}

// Function to perform lexical analysis using the DFA
struct tokens tokenize(struct finite_automata *intput_dfa,int ** types,struct type *type, int types_num, const char *input,int *count,int *num){
    struct _finite_automata *dfa = build_next_state(intput_dfa,types,type,types_num,count,num);
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
                struct token *new_tokens = realloc(result.tokens, sizeof(struct token) * capacity);
                if (new_tokens == NULL) {
                    fprintf(stderr, "Error: Failed to reallocate memory for tokens.\n");
                    free(token);
                    free_tokens(&result);
                    free_dfa(dfa);
                    struct tokens empty = {NULL, 0};
                    return empty;
                }
                result.tokens = new_tokens;
            }
            position = last_accepting_position;
        }
    }

    free_dfa(dfa);
    return result;
}

// Function to free the types
void free_types(struct type *types, int n) {
    for (int i = 0; i < n; i++) {
        free(types[i].name);
    }
    free(types);
}

void print_token(struct tokens tokens) {
    for (int i = 0; i < tokens.n; i++) {
        printf("Token: %s, Type: %s\n", tokens.tokens[i].value, tokens.tokens[i].type->name);
    }
}