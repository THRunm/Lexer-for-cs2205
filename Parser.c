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


struct frontend_regexp * string_to_frontend_regexp(char ** str){
    return Parser(*str);
}

struct frontend_regexp * Parser(char * str){

}

struct frontend_regexp * Parse_CHAR_SET(char * str){

}


struct frontend_regexp * Parse_OPTION(char * str){

}

struct frontend_regexp * Parse_STAR(char * str){

}

struct frontend_regexp * Parse_PLUS(char * str){

}

struct frontend_regexp * Parse_STRING(char * str){

}

struct frontend_regexp * Parse_SINGLE_CHAR(char * str){

}

struct frontend_regexp * Parse_UNION(char * str){

}

struct frontend_regexp * Parse_CONCAT(char * str){

}
