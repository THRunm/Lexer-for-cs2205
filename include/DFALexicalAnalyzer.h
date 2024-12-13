//
// Created by asus on 24-11-20.
//

#ifndef GRAMMAR_PARSER_FOR_CS2205_DFALEXICALANALYZER_H
#define GRAMMAR_PARSER_FOR_CS2205_DFALEXICALANALYZER_H

struct type {
    char *name;
    int id;
};

struct token {
    char *value;
    struct type *type;
};
struct tokens {
    struct token *tokens;
    int n;
};

struct _finite_automata {
    int n; /* number of vertices, id of vertices are: 0, 1, ..., (n - 1) */
    int m; /* number of edges, id of edges are: 0, 1, ..., (m - 1) */
    int *src; /* for every edge e, src[e] is the source vertex of e */
    int *dst; /* for every edge e, dst[e] is the destination vertex of e */
    struct char_set *lb; /* for every edge e, lb[e] are the transition labels on e, if the char set is empty, the edge is an epsilon edge */

    struct type **accepting_token_type; /* size n, accepting_token_type[s] is -1 if state s is not accepting, or the token type otherwise */
    int **next_state; /* size n x 256, next_state[s][c] = next state when in state s and reading c, or -1 if no transition */
};

// Function to perform lexical analysis using the DFA
void free_tokens(struct tokens *tokens);
// Function to free the DFA
void free_dfa(struct _finite_automata *dfa);
// Function to build the next_state transition table
struct _finite_automata * build_next_state(struct finite_automata *dfa,const int ** types,struct type* type, int types_num,int *count,int *num);
// Function to perform lexical analysis using the DFA
struct tokens tokenize(struct finite_automata *intput_dfa, int **types,struct type *type, int types_num, const char *input,int *count,int *num);

void print_token(struct tokens tokens);

#endif //GRAMMAR_PARSER_FOR_CS2205_DFALEXICALANALYZER_H
