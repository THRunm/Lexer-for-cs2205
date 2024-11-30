#include "RegexToNFA.h"

struct finite_automata *nfa;
int siz = 32;
struct char_set EMPTY = {NULL, 0};

struct finite_automata * create_empty_graph() {
    struct finite_automata* nfa = (struct finite_automata*)malloc(sizeof(struct finite_automata));
    nfa->n = nfa->m = 0;
    nfa->src = (int*)calloc(siz, sizeof(int));
    nfa->dst = (int*)calloc(siz, sizeof(int));
    nfa->lb = (struct char_set*)calloc(siz, sizeof(struct char_set));
    return nfa;
}

int add_one_vertex(struct finite_automata * g) {
    g->n++;
    return g->n - 1;
}

int add_one_edge(struct finite_automata * g, int src, int dst, struct char_set * c) {
    g->m++;
    int nw = g->m - 1;
    if (nw >= siz) {
        siz <<= 1;
        g->src = (int*)realloc(g->src, siz * sizeof(int));
        g->dst = (int*)realloc(g->dst, siz * sizeof(int));
        g->lb = (struct char_set*)realloc(g->lb, siz * sizeof(struct char_set));
    }
    g->src[nw] = src;
    g->dst[nw] = dst;
    g->lb[nw] = *c;
    char *s = (char*)malloc(c->n * sizeof(char));
    memcpy(s, c->c, c->n * sizeof(char));
    g->lb[nw].c = s;
}

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

struct NFA* build_nfa(struct simpl_regexp * x) {
    nfa = create_empty_graph();
    struct component * res = build(x);
    struct NFA * ret = (struct NFA*)malloc(sizeof(struct NFA));
    ret->comp = res, ret->nfa = nfa;
    return ret;
}

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