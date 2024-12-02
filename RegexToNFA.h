#ifndef GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
#define GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H

#include "lang.h"

struct component {
    int src, dst;
};

struct component* build(struct simpl_regexp* x);

struct finite_automata * build_nfa(struct simpl_regexp * x, int * src, int * dst);

void print(struct finite_automata * g);

#endif //GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
