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
};*/

/*
优先级：\转义 > 括号 > CHAR_SET = STRING = SINGLE_CHAR > OPTION = STAR = PLUS > CONCAT > UNION 
*/


struct frontend_regexp * string_to_frontend_regexp(char ** str){
    return Parser(*str);
}

struct frontend_regexp * Parser(char * str){

}