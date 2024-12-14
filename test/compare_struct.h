#ifndef COMPARE_STRUCT_H_INCLUDED
#define COMPARE_STRUCT_H_INCLUDED

#include "lang.h"

// Compare two character sets
bool compare_char_set(struct char_set* cs1, struct char_set* cs2);

// Compare two frontend regular expressions
bool compare_frontend_regexp(struct frontend_regexp* r1, struct frontend_regexp* r2);

// Compare two simplified regular expressions
bool compare_simpl_regexp(struct simpl_regexp* r1, struct simpl_regexp* r2);

// Compare two finite automata
bool compare_finite_automata(struct finite_automata* fa1, struct finite_automata* fa2);

#endif // COMPARE_STRUCT_H_INCLUDED