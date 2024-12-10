//
// Created by asus on 24-11-20.
//

#include "SimplifyRegex.h"


#include "lang.h"

struct simpl_regexp * transform_to_simplified(struct frontend_regexp *r) {
    if (!r) return NULL;

    switch (r->t) {
        case T_FR_CHAR_SET: {
            return TS_CharSet(&r->d.CHAR_SET);
        }
        case T_FR_OPTIONAL: {
            struct simpl_regexp *simpl_r = transform_to_simplified(r->d.OPTION.r);
            return TS_Union(simpl_r, TS_EmptyStr());
        }
        case T_FR_STAR: {
            struct simpl_regexp *simpl_r = transform_to_simplified(r->d.STAR.r);
            return TS_Star(simpl_r);
        }
        case T_FR_PLUS: {
            struct simpl_regexp *simpl_r = transform_to_simplified(r->d.PLUS.r);
            return TS_Concat(simpl_r, TS_Star(simpl_r));
        }
        case T_FR_STRING: {
            char *str = r->d.STRING.s;
            if (!str || str[0] == '\0') return TS_EmptyStr();

            struct simpl_regexp *result = TS_CharSet(&(struct char_set){ .c = str, .n = 1 });
            for (int i = 1; str[i] != '\0'; ++i) {
                struct simpl_regexp *next_char = TS_CharSet(&(struct char_set){ .c = &str[i], .n = 1 });
                result = TS_Concat(result, next_char);
            }
            return result;
        }
        case T_FR_SINGLE_CHAR: {
            return TS_CharSet(&(struct char_set){ .c = &r->d.SINGLE_CHAR.c, .n = 1 });
        }
        case T_FR_UNION: {
            struct simpl_regexp *r1 = transform_to_simplified(r->d.UNION.r1);
            struct simpl_regexp *r2 = transform_to_simplified(r->d.UNION.r2);
            return TS_Union(r1, r2);
        }
        case T_FR_CONCAT: {
            struct simpl_regexp *r1 = transform_to_simplified(r->d.CONCAT.r1);
            struct simpl_regexp *r2 = transform_to_simplified(r->d.CONCAT.r2);
            return TS_Concat(r1, r2);
        }
        default:
            return NULL;
    }
}
