#include "Parser.h"

struct frontend_regexp *parse_expression(const char **input);
struct frontend_regexp *parse_primary(const char **input);
struct frontend_regexp *parse_concat(const char **input);
struct frontend_regexp *parse_union(const char **input);
struct frontend_regexp *parse_star(const char **input);
struct frontend_regexp *parse_option(const char **input);
struct frontend_regexp *parse_plus(const char **input);

// Helper functions to create regex components
struct frontend_regexp *create_single_char(char c) {
    return TFr_SingleChar(c);
}

struct frontend_regexp *create_string(const char *s) {
    return TFr_String(strdup(s));
}

struct frontend_regexp *create_union(struct frontend_regexp *r1, struct frontend_regexp *r2) {
    return TFr_Union(r1, r2);
}

struct frontend_regexp *create_concat(struct frontend_regexp *r1, struct frontend_regexp *r2) {
    return TFr_Concat(r1, r2);
}

struct frontend_regexp *create_star(struct frontend_regexp *r) {
    return TFr_Star(r);
}

struct frontend_regexp *create_option(struct frontend_regexp *r) {
    return TFr_Option(r);
}

struct frontend_regexp *create_plus(struct frontend_regexp *r) {
    return TFr_Plus(r);
}

// Recursive descent parsing functions
struct frontend_regexp *parse_expression(const char **input) {
    return parse_union(input);
}

struct frontend_regexp *parse_union(const char **input) {
    struct frontend_regexp *r1 = parse_concat(input);
    while (**input == '|') {
        (*input)++;
        struct frontend_regexp *r2 = parse_concat(input);
        r1 = create_union(r1, r2);
    }
    return r1;
}

struct frontend_regexp *parse_concat(const char **input) {
    struct frontend_regexp *r1 = parse_primary(input);
    while (**input && **input != '|' && **input != ')' && **input != '?' && **input != '*' && **input != '+') {
        struct frontend_regexp *r2 = parse_primary(input);
        r1 = create_concat(r1, r2);
    }
    return r1;
}

struct frontend_regexp *parse_primary(const char **input) {
    if (**input == '(') {
        (*input)++;
        struct frontend_regexp *r = parse_expression(input);
        if (**input == ')') {
            (*input)++;
        }
        return r;
    } else if (**input == '\\') {
        (*input)++;
        return create_single_char(*((*input)++));
    } else {
        return create_single_char(*((*input)++));
    }
}

}