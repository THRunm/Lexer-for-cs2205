#include "Parser.h"

/*struct frontend_regexp {
  enum FrontendRegExpType t;
  union {
    struct char_set CHAR_SET;
    struct {struct frontend_regexp * r; } OPTION;
    struct {struct frontend_regexp * r; } STAR;
    struct {struct frontend_regexp * r; } PLUS;
    struct {char * s; } STRING;
    struct {char c; } SINGLE_CHAR;
    struct {struct frontend_regexp * r1; struct frontend_regexp * r2; } UNION;
    struct {struct frontend_regexp * r1; struct frontend_regexp * r2; } CONCAT;
  } d;
};

void copy_char_set(struct char_set * dst, struct char_set * src);
struct frontend_regexp * TFr_CharSet(struct char_set * c);
struct frontend_regexp * TFr_Option(struct frontend_regexp * r);
struct frontend_regexp * TFr_Star(struct frontend_regexp * r);
struct frontend_regexp * TFr_Plus(struct frontend_regexp * r);
struct frontend_regexp * TFr_String(char * s);
struct frontend_regexp * TFr_SingleChar(char c);
struct frontend_regexp * TFr_Union(struct frontend_regexp * r1, struct frontend_regexp * r2);
struct frontend_regexp * TFr_Concat(struct frontend_regexp * r1, struct frontend_regexp * r2);
*/

/*
优先级： 括号 > CHAR_SET([char1char2...]表示) = STRING({string}表示) = SINGLE_CHAR > OPTION(r?表示) = STAR(r*表示) = PLUS(r+表示) > CONCAT(r1r2表示) > UNION(r1|r2表示) 
*/


void skip_spaces(char **str) {
    while (**str == ' ' || **str == '\t' || **str == '\n') {
        (*str)++;
    }
}

int match(char **str, char c) {
    skip_spaces(str);
    if (**str == c) {
        (*str)++;
        return 1;
    }
    return 0;
}

// Main parser entry point
struct frontend_regexp * Parser(char *str) {
    return Parse_UNION(&str);
}

// Parse UNION (r1 | r2)
struct frontend_regexp * Parse_UNION(char **str) {
    struct frontend_regexp *left = Parse_CONCAT(str);
    skip_spaces(str);
    while (match(str, '|')) {
        struct frontend_regexp *right = Parse_CONCAT(str);
        left = TFr_Union(left, right);
    }
    return left;
}

// Parse CONCAT (r1 r2)
struct frontend_regexp * Parse_CONCAT(char **str) {
    struct frontend_regexp *left = Parse_CHAR_SET(str);
    skip_spaces(str);
    while (**str && **str != '|' && **str != ')') {
        struct frontend_regexp *right = Parse_CHAR_SET(str);
        left = TFr_Concat(left, right);
    }
    return left;
}

// Parse CHAR_SET, STRING, SINGLE_CHAR
struct frontend_regexp * Parse_CHAR_SET(char **str) {
    skip_spaces(str);
    if (match(str, '[')) {
        struct char_set charset;
        memset(&charset, 0, sizeof(charset));
        while (**str && **str != ']') {
            // Assuming the char_set struct can hold individual characters
            charset.chars[charset.count++] = *(*str)++;
        }
        if (match(str, ']')) {
            return TFr_CharSet(&charset);
        }
    }
    return Parse_STRING(str);
}

struct frontend_regexp * Parse_STRING(char **str) {
    skip_spaces(str);
    if (**str == '{') {
        (*str)++;
        char buffer[256];
        int i = 0;
        while (**str && **str != '}') {
            buffer[i++] = *(*str)++;
        }
        buffer[i] = '\0';
        if (match(str, '}')) {
            return TFr_String(strdup(buffer));
        }
    }
    return Parse_SINGLE_CHAR(str);
}

struct frontend_regexp * Parse_SINGLE_CHAR(char **str) {
    skip_spaces(str);
    if (**str && **str != '|' && **str != ')' && **str != '*' && **str != '+' && **str != '?') {
        char c = *(*str)++;
        struct frontend_regexp *base = TFr_SingleChar(c);
        return Parse_OPTION_STAR_PLUS(str, base);
    }
    return NULL;
}

// Parse OPTION (?), STAR (*), PLUS (+) after a base regex
struct frontend_regexp * Parse_OPTION_STAR_PLUS(char **str, struct frontend_regexp *base) {
    skip_spaces(str);
    if (match(str, '?')) {
        return TFr_Option(base);
    } else if (match(str, '*')) {
        return TFr_Star(base);
    } else if (match(str, '+')) {
        return TFr_Plus(base);
    }
    return base;
}

