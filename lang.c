#include "lang.h"

void copy_char_set(struct char_set * dst, struct char_set * src){
    dst->c = src->c;
    dst->n = src->n;
}

struct frontend_regexp * TFr_CharSet(struct char_set * c){
    struct frontend_regexp * r = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    r->t = T_FR_CHAR_SET;
    copy_char_set(&(r->d.CHAR_SET), c);
    return r;
}

struct frontend_regexp * TFr_Option(struct frontend_regexp * r);
struct frontend_regexp * TFr_Star(struct frontend_regexp * r);
struct frontend_regexp * TFr_Plus(struct frontend_regexp * r);
struct frontend_regexp * TFr_String(char * s);
struct frontend_regexp * TFr_SingleChar(char c);
struct frontend_regexp * TFr_Union(struct frontend_regexp * r1, struct frontend_regexp * r2);
struct frontend_regexp * TFr_Concat(struct frontend_regexp * r1, struct frontend_regexp * r2);
struct simpl_regexp * TS_CharSet(struct char_set * c);
struct simpl_regexp * TS_Star(struct simpl_regexp * r);
struct simpl_regexp * TS_EmptyStr();
struct simpl_regexp * TS_Union(struct simpl_regexp * r1, struct simpl_regexp * r2);
struct simpl_regexp * TS_Concat(struct simpl_regexp * r1, struct simpl_regexp * r2);
struct finite_automata * create_empty_graph();