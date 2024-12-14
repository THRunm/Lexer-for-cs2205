#include "RegexToNFA.h"

struct finite_automata *nfa;
struct char_set EMPTY = {NULL, 0};

// build NFA from the given simplified regular expression.
// return the start and end vertex of the NFA.
struct component* build(struct simpl_regexp* x) {
  int S, T;
  if (x->t == T_S_CHAR_SET) {
    S = add_one_vertex(nfa);
    T = add_one_vertex(nfa);
    struct char_set c = x->d.CHAR_SET;
    add_one_edge(nfa, S, T, &c);
  } else if (x->t == T_S_STAR) {
    S = add_one_vertex(nfa);
    T = add_one_vertex(nfa);
    struct component * res = build(x->d.STAR.r);
    add_one_edge(nfa, S, res->dst, &EMPTY);
    add_one_edge(nfa, res->dst, res->src, &EMPTY);
    add_one_edge(nfa, res->dst, T, &EMPTY);
  } else if (x->t == T_S_EMPTY_STR) {
    S = add_one_vertex(nfa);
    T = add_one_vertex(nfa);
    add_one_edge(nfa, S, T, &EMPTY);
  } else if (x->t == T_S_UNION) {
    S = add_one_vertex(nfa);
    T = add_one_vertex(nfa);
    struct component * res1 = build(x->d.UNION.r1);
    struct component * res2 = build(x->d.UNION.r2);
    add_one_edge(nfa, S, res1->src, &EMPTY);
    add_one_edge(nfa, S, res2->src, &EMPTY);
    add_one_edge(nfa, res1->dst, T, &EMPTY);
    add_one_edge(nfa, res2->dst, T, &EMPTY);
  } else if (x->t == T_S_CONCAT) {
    struct component * res1 = build(x->d.CONCAT.r1);
    struct component * res2 = build(x->d.CONCAT.r2);
    S = res1->src, T = res2->dst;
    add_one_edge(nfa, res1->dst, res2->src, &EMPTY);
  }
  struct component * res = (struct component*)malloc(sizeof(struct component));
  res->src = S, res->dst = T;
  return res;
}

// build NFA from the given simplified regular expression.
struct finite_automata * build_nfa(struct simpl_regexp * x, int * src, int * dst) {
  nfa = create_empty_graph();
  struct component * res = build(x);
  *src = res->src, *dst = res->dst;
  return nfa;
}

// print the NFA.
void print(struct finite_automata * g) {
  printf("n = %d, m = %d\n", g->n, g->m);
  for (int i = 0; i < g->m; i++) {
    printf("src = %d, dst = %d, lb = ", g->src[i], g->dst[i]);
    for (int j = 0; j < g->lb[i].n; j++) {
      printf("%c", g->lb[i].c[j]);
    }
    printf("\n");
  }
}