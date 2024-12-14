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
  //TODO 内存未释放
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

void print_frontend_regexp(struct frontend_regexp *re) {
  print_frontend_regexp_rec(re);
  printf("\n");
}

void print_frontend_regexp_rec(struct frontend_regexp *re) {
  if (!re) return;
  bool flag;
  switch (re->t) {
  case T_FR_CHAR_SET:
    printf("[");
    for (unsigned int i = 0; i < re->d.CHAR_SET.n; i++) {
      printf("%c", re->d.CHAR_SET.c[i]);
    }
    printf("]");
    break;
  case T_FR_OPTIONAL:
    if (re->d.OPTION.r->t == T_FR_UNION || re->d.OPTION.r->t == T_FR_CONCAT) printf("(");
    print_frontend_regexp_rec(re->d.OPTION.r);
    if (re->d.OPTION.r->t == T_FR_UNION || re->d.OPTION.r->t == T_FR_CONCAT) printf(")");
    printf("?");
    break;
  case T_FR_STAR:
    if (re->d.STAR.r->t == T_FR_UNION || re->d.STAR.r->t == T_FR_CONCAT) printf("(");
    print_frontend_regexp_rec(re->d.STAR.r);
    if (re->d.STAR.r->t == T_FR_UNION || re->d.STAR.r->t == T_FR_CONCAT) printf(")");
    printf("*");
    break;
  case T_FR_PLUS:
    if (re->d.PLUS.r->t == T_FR_UNION || re->d.PLUS.r->t == T_FR_CONCAT) printf("(");
    print_frontend_regexp_rec(re->d.PLUS.r);
    if (re->d.PLUS.r->t == T_FR_UNION || re->d.PLUS.r->t == T_FR_CONCAT) printf(")");
    printf("+");
    break;
  case T_FR_STRING:
    printf("%s", re->d.STRING.s);
    break;
  case T_FR_SINGLE_CHAR:
    printf("%c", re->d.SINGLE_CHAR.c);
    break;
  case T_FR_UNION:
    if (re->d.UNION.r1->t == T_FR_CONCAT) printf("(");
    print_frontend_regexp_rec(re->d.UNION.r1);
    if (re->d.UNION.r1->t == T_FR_CONCAT) printf(")");
    printf("|");
    if (re->d.UNION.r2->t == T_FR_CONCAT) printf("(");
    print_frontend_regexp_rec(re->d.UNION.r2);
    if (re->d.UNION.r2->t == T_FR_CONCAT) printf(")");
    break;
  case T_FR_CONCAT:
    print_frontend_regexp_rec(re->d.CONCAT.r1);
    if (re->d.CONCAT.r2->t == T_FR_UNION) printf("(");
    print_frontend_regexp_rec(re->d.CONCAT.r2);
    if (re->d.CONCAT.r2->t == T_FR_UNION) printf(")");
    break;
  default:
    printf("(Unknown frontend_regexp type)");
  }
}

void print_simpl_regexp(struct simpl_regexp *re) {
  print_simpl_regexp_rec(re);
  printf("\n");
}

void print_simpl_regexp_rec(struct simpl_regexp *re) {
  if (!re) return;

  switch (re->t) {
  case T_S_CHAR_SET:
    printf("[");
    for (unsigned int i = 0; i < re->d.CHAR_SET.n; i++) {
      printf("%c", re->d.CHAR_SET.c[i]);
    }
    printf("]");
    break;
  case T_S_STAR:
    print_simpl_regexp_rec(re->d.STAR.r);
    printf("*");
    break;
  case T_S_EMPTY_STR:
    printf("ε");
    break;
  case T_S_UNION:
    print_simpl_regexp_rec(re->d.UNION.r1);
    printf("|");
    print_simpl_regexp_rec(re->d.UNION.r2);
    break;
  case T_S_CONCAT:
    print_simpl_regexp_rec(re->d.CONCAT.r1);
    print_simpl_regexp_rec(re->d.CONCAT.r2);
    break;
  default:
    printf("(Unknown simpl_regexp type)");
  }
}

void free_frontend_regexp(struct frontend_regexp **fr) {
  if (!fr || !*fr) return;
  *fr = NULL;  // 通过二级指针修改原指针
}

void free_frontend_regexp_rec(struct frontend_regexp *fr) {
  if (!fr) return;

  switch (fr->t) {
  case T_FR_CHAR_SET:
    if (fr->d.CHAR_SET.c) {
      //free(fr->d.CHAR_SET.c);
      fr->d.CHAR_SET.c = NULL;
    }
    break;
  case T_FR_OPTIONAL:
    if (fr->d.OPTION.r) {
      free_frontend_regexp_rec(fr->d.OPTION.r);  // 使用_rec版本避免重复释放
      free(fr->d.OPTION.r);
      fr->d.OPTION.r = NULL;
    }
    break;
  case T_FR_STAR:
    if (fr->d.STAR.r) {
      free_frontend_regexp_rec(fr->d.STAR.r);
      free(fr->d.STAR.r);
      fr->d.STAR.r = NULL;
    }
    break;
  case T_FR_PLUS:
    if (fr->d.PLUS.r) {
      free_frontend_regexp_rec(fr->d.PLUS.r);
      free(fr->d.PLUS.r);
      fr->d.PLUS.r = NULL;
    }
    break;
  case T_FR_STRING:
    if (fr->d.STRING.s) {
      //free(fr->d.STRING.s);
      fr->d.STRING.s = NULL;
    }
    break;
  case T_FR_SINGLE_CHAR:
    break;
  case T_FR_UNION:
    if (fr->d.UNION.r1) {
      free_frontend_regexp_rec(fr->d.UNION.r1);
      free(fr->d.UNION.r1);
      fr->d.UNION.r1 = NULL;
    }
    if (fr->d.UNION.r2) {
      free_frontend_regexp_rec(fr->d.UNION.r2);
      free(fr->d.UNION.r2);
      fr->d.UNION.r2 = NULL;
    }
    break;
  case T_FR_CONCAT:
    if (fr->d.CONCAT.r1) {
      free_frontend_regexp_rec(fr->d.CONCAT.r1);
      free(fr->d.CONCAT.r1);
      fr->d.CONCAT.r1 = NULL;
    }
    if (fr->d.CONCAT.r2) {
      free_frontend_regexp_rec(fr->d.CONCAT.r2);
      free(fr->d.CONCAT.r2);
      fr->d.CONCAT.r2 = NULL;
    }
    break;
  default:
    break;
  }
}

void free_simpl_regexp(struct simpl_regexp **sr) {
  if (!sr || !*sr) return;
  *sr = NULL;
}

void free_simpl_regexp_rec(struct simpl_regexp *sr) {
  if (!sr) return;

  switch (sr->t) {
  case T_S_CHAR_SET:
    if (sr->d.CHAR_SET.c) {
      //free(sr->d.CHAR_SET.c);
      sr->d.CHAR_SET.c = NULL;
    }
    break;
  case T_S_STAR:
    if (sr->d.STAR.r) {
      free_simpl_regexp_rec(sr->d.STAR.r);
      free(sr->d.STAR.r);
      sr->d.STAR.r = NULL;
    }
    break;
  case T_S_UNION:
    if (sr->d.UNION.r1) {
      free_simpl_regexp_rec(sr->d.UNION.r1);
      free(sr->d.UNION.r1);
      sr->d.UNION.r1 = NULL;
    }
    if (sr->d.UNION.r2) {
      free_simpl_regexp_rec(sr->d.UNION.r2);
      free(sr->d.UNION.r2);
      sr->d.UNION.r2 = NULL;
    }
    break;
  case T_S_CONCAT:
    if (sr->d.CONCAT.r1) {
      free_simpl_regexp_rec(sr->d.CONCAT.r1);
      free(sr->d.CONCAT.r1);
      sr->d.CONCAT.r1 = NULL;
    }
    if (sr->d.CONCAT.r2) {
      free_simpl_regexp_rec(sr->d.CONCAT.r2);
      free(sr->d.CONCAT.r2);
      sr->d.CONCAT.r2 = NULL;
    }
    break;
  case T_S_EMPTY_STR:
    break;
  default:
    break;
  }
}

