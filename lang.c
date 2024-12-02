#include "lang.h"

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

void string_to_frontend_regexp(char * s, struct frontend_regexp * r){
      
}