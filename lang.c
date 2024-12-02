#include "lang.h"
#include <string.h>

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