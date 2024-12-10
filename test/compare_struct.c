#include "compare_struct.h"
#include <string.h>

bool compare_char_set(struct char_set* cs1, struct char_set* cs2) {
    if (cs1 == cs2) return 1; // Same pointer
    if (cs1 == NULL || cs2 == NULL) return 0;
    if (cs1->n != cs2->n) return 0;
    
    // Compare each character
    for (unsigned int i = 0; i < cs1->n; i++) {
        if (cs1->c[i] != cs2->c[i]) return 0;
    }
    return 1;
}

bool compare_frontend_regexp(struct frontend_regexp* r1, struct frontend_regexp* r2) {
    if (r1 == r2) return 1; // Same pointer
    if (r1 == NULL || r2 == NULL) return 0;
    if (r1->t != r2->t) return 0;

    switch (r1->t) {
        case T_FR_CHAR_SET:
            return compare_char_set(&r1->d.CHAR_SET, &r2->d.CHAR_SET);
            
        case T_FR_OPTIONAL:
            return compare_frontend_regexp(r1->d.OPTION.r, r2->d.OPTION.r);
            
        case T_FR_STAR:
            return compare_frontend_regexp(r1->d.STAR.r, r2->d.STAR.r);
            
        case T_FR_PLUS:
            return compare_frontend_regexp(r1->d.PLUS.r, r2->d.PLUS.r);
            
        case T_FR_STRING:
            return (strcmp(r1->d.STRING.s, r2->d.STRING.s) == 0);
            
        case T_FR_SINGLE_CHAR:
            return (r1->d.SINGLE_CHAR.c == r2->d.SINGLE_CHAR.c);
            
        case T_FR_UNION:
            return compare_frontend_regexp(r1->d.UNION.r1, r2->d.UNION.r1) &&
                   compare_frontend_regexp(r1->d.UNION.r2, r2->d.UNION.r2);
                   
        case T_FR_CONCAT:
            return compare_frontend_regexp(r1->d.CONCAT.r1, r2->d.CONCAT.r1) &&
                   compare_frontend_regexp(r1->d.CONCAT.r2, r2->d.CONCAT.r2);
            
        default:
            return 0;
    }
}

bool compare_simpl_regexp(struct simpl_regexp* r1, struct simpl_regexp* r2) {
    if (r1 == r2) return 1; // Same pointer
    if (r1 == NULL || r2 == NULL) return 0;
    if (r1->t != r2->t) return 0;

    switch (r1->t) {
        case T_S_CHAR_SET:
            return compare_char_set(&r1->d.CHAR_SET, &r2->d.CHAR_SET);
            
        case T_S_STAR:
            return compare_simpl_regexp(r1->d.STAR.r, r2->d.STAR.r);
            
        case T_S_EMPTY_STR:
            return 1; // Both are empty strings
            
        case T_S_UNION:
            return compare_simpl_regexp(r1->d.UNION.r1, r2->d.UNION.r1) &&
                   compare_simpl_regexp(r1->d.UNION.r2, r2->d.UNION.r2);
                   
        case T_S_CONCAT:
            return compare_simpl_regexp(r1->d.CONCAT.r1, r2->d.CONCAT.r1) &&
                   compare_simpl_regexp(r1->d.CONCAT.r2, r2->d.CONCAT.r2);
            
        default:
            return 0;
    }
}

bool compare_finite_automata(struct finite_automata* fa1, struct finite_automata* fa2) {
    if (fa1 == fa2) return 1; // Same pointer
    if (fa1 == NULL || fa2 == NULL) return 0;
    
    // Compare basic properties
    if (fa1->n != fa2->n || fa1->m != fa2->m || fa1->siz != fa2->siz) 
        return 0;
    
    // Compare edges
    for (int i = 0; i < fa1->m; i++) {
        if (fa1->src[i] != fa2->src[i] || 
            fa1->dst[i] != fa2->dst[i] ||
            !compare_char_set(&fa1->lb[i], &fa2->lb[i])) {
            return 0;
        }
    }
    
    return 1;
}