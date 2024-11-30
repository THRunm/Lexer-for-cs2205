#ifndef GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
#define GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H

#include "lang.h"
#include <string.h>

struct component {
    int src, dst;
};

struct NFA {
    struct component * comp;
    struct finite_automata * nfa;
};

struct component* build(struct simpl_regexp* x);

struct NFA* build_nfa(struct simpl_regexp * x);

void print(struct finite_automata * g);

#endif //GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
