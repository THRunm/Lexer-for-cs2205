#include "lang.h"
#include <string.h>

void copy_char_set(struct char_set * dst, struct char_set * src){
    dst->c = src->c;
    dst->n = src->n;
}

struct frontend_regexp * TFr_CharSet(struct char_set * c){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_CHAR_SET;
    copy_char_set(&(ret->d.CHAR_SET), c);
    return ret;
}

struct frontend_regexp * TFr_Option(struct frontend_regexp * r){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_OPTIONAL;
    ret->d.OPTION.r = r;
    return ret;
}

struct frontend_regexp * TFr_Star(struct frontend_regexp * r){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_STAR;
    ret->d.STAR.r = r;
    return ret;
}

struct frontend_regexp * TFr_Plus(struct frontend_regexp * r){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_PLUS;
    ret->d.PLUS.r = r;
    return ret;
}

struct frontend_regexp * TFr_String(char * s){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_STRING;
    ret->d.STRING.s = s;
    return ret;
}

struct frontend_regexp * TFr_SingleChar(char c){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_SINGLE_CHAR;
    ret->d.SINGLE_CHAR.c = c;
    return ret;
}

struct frontend_regexp * TFr_Union(struct frontend_regexp * r1, struct frontend_regexp * r2){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_UNION;
    ret->d.UNION.r1 = r1;
    ret->d.UNION.r2 = r2;
    return ret;
}

struct frontend_regexp * TFr_Concat(struct frontend_regexp * r1, struct frontend_regexp * r2){
    struct frontend_regexp * ret = (struct frontend_regexp *)malloc(sizeof(struct frontend_regexp));
    ret->t = T_FR_CONCAT;
    ret->d.CONCAT.r1 = r1;
    ret->d.CONCAT.r2 = r2;
    return ret;
}

struct simpl_regexp * TS_CharSet(struct char_set * c){
    struct simpl_regexp * ret = (struct simpl_regexp *)malloc(sizeof(struct simpl_regexp));
    ret->t = T_S_CHAR_SET;
    copy_char_set(&(ret->d.CHAR_SET), c);
    return ret;
}

struct simpl_regexp * TS_Star(struct simpl_regexp * r){
    struct simpl_regexp * ret = (struct simpl_regexp *)malloc(sizeof(struct simpl_regexp));
    ret->t = T_S_STAR;
    ret->d.STAR.r = r;
    return ret; 
}

struct simpl_regexp * TS_EmptyStr(){
    struct simpl_regexp * ret = (struct simpl_regexp *)malloc(sizeof(struct simpl_regexp));
    ret->t = T_S_EMPTY_STR;
    return ret;
}

struct simpl_regexp * TS_Union(struct simpl_regexp * r1, struct simpl_regexp * r2){
    struct simpl_regexp * ret = (struct simpl_regexp *)malloc(sizeof(struct simpl_regexp));
    ret->t = T_S_UNION;
    ret->d.UNION.r1 = r1;
    ret->d.UNION.r2 = r2;
    return ret;
}

struct simpl_regexp * TS_Concat(struct simpl_regexp * r1, struct simpl_regexp * r2){
    struct simpl_regexp * ret = (struct simpl_regexp *)malloc(sizeof(struct simpl_regexp));
    ret->t = T_S_CONCAT;
    ret->d.CONCAT.r1 = r1;
    ret->d.CONCAT.r2 = r2;
    return ret;
}

const int SIZ = 32;

struct finite_automata * create_empty_graph() {
    struct finite_automata* g = (struct finite_automata*)malloc(sizeof(struct finite_automata));
    g->n = g->m = 0, g->siz = SIZ;
    g->src = (int*)calloc(SIZ, sizeof(int));
    g->dst = (int*)calloc(SIZ, sizeof(int));
    g->lb = (struct char_set*)calloc(SIZ, sizeof(struct char_set));
    return g;
}

int add_one_vertex(struct finite_automata * g) {
    g->n++;
    return g->n - 1;
}

int add_one_edge(struct finite_automata * g, int src, int dst, struct char_set * c) {
    g->m++;
    int nw = g->m - 1;
    if (nw >= g->siz) {
        g->siz <<= 1;
        g->src = (int*)realloc(g->src, g->siz * sizeof(int));
        g->dst = (int*)realloc(g->dst, g->siz * sizeof(int));
        g->lb = (struct char_set*)realloc(g->lb, g->siz * sizeof(struct char_set));
    }
    g->src[nw] = src;
    g->dst[nw] = dst;
    g->lb[nw] = *c;
    char *s = (char*)malloc(c->n * sizeof(char));
    memcpy(s, c->c, c->n * sizeof(char));
    g->lb[nw].c = s;
    return nw;
}

struct frontend_regexp * string_to_frontend_regexp(struct frontend_regexp * r){
    
}

char * frontend_regexp_to_string(struct frontend_regexp * r){
    char *result = NULL;
    char *temp1 = NULL;
    char *temp2 = NULL;

    switch (r->t) {
        case T_FR_SINGLE_CHAR:
            result = malloc(2);
            result[0] = r->d.SINGLE_CHAR.c;
            result[1] = '\0';
            break;

        case T_FR_STRING:
            result = strdup(r->d.STRING.s);
            break;

        case T_FR_CONCAT:
            temp1 = frontend_regexp_to_string(r->d.CONCAT.r1);
            temp2 = frontend_regexp_to_string(r->d.CONCAT.r2);
            result = malloc(strlen(temp1) + strlen(temp2) + 1);
            sprintf(result, "%s%s", temp1, temp2);
            free(temp1);
            free(temp2);
            break;

        case T_FR_UNION:
            temp1 = frontend_regexp_to_string(r->d.UNION.r1);
            temp2 = frontend_regexp_to_string(r->d.UNION.r2);
            result = malloc(strlen(temp1) + strlen(temp2) + 3);
            sprintf(result, "(%s|%s)", temp1, temp2);
            free(temp1);
            free(temp2);
            break;

        case T_FR_STAR:
            temp1 = frontend_regexp_to_string(r->d.STAR.r);
            result = malloc(strlen(temp1) + 2);
            sprintf(result, "%s*", temp1);
            free(temp1);
            break;

        case T_FR_OPTIONAL:
            temp1 = frontend_regexp_to_string(r->d.OPTION.r);
            result = malloc(strlen(temp1) + 2);
            sprintf(result, "%s?", temp1);
            free(temp1);
            break;

        case T_FR_PLUS:
            temp1 = frontend_regexp_to_string(r->d.PLUS.r);
            result = malloc(strlen(temp1) + 2);
            sprintf(result, "%s+", temp1);
            free(temp1);
            break;

        default:
            result = strdup("");
            break;
    }
    return result;
}

char * simpl_regexp_to_string(struct simpl_regexp * r){
         
}