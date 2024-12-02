#include "lang.h"

void copy_char_set(struct char_set * dst, struct char_set * src){
    dst->c = src->c;
    dst->n = src->n;
}