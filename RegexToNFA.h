#ifndef GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
#define GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H

#include "lang.h"

struct component {
    int src, dst;
};

// build NFA from the given simplified regular expression.
// return the start and end vertex of the NFA.
struct component* build(struct simpl_regexp* x);

// build NFA from the given simplified regular expression.
struct finite_automata * build_nfa(struct simpl_regexp * x, int * src, int * dst);

// print the NFA.
void print(struct finite_automata * g);

#endif //GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H
