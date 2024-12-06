#include "lang.h"

#ifndef PARSER_H
#define PARSER_H
 
struct frontend_regexp * string_to_frontend_regexp(char ** str); // convert a string to a frontend regexp 

struct frontend_regexp * Parser(char * str);

struct frontend_regexp * Parse_CHAR_SET(char * str);

struct frontend_regexp * Parse_OPTION(char * str);

struct frontend_regexp * Parse_STAR(char * str);

struct frontend_regexp * Parse_PLUS(char * str);

struct frontend_regexp * Parse_STRING(char * str);

struct frontend_regexp * Parse_SINGLE_CHAR(char * str);

struct frontend_regexp * Parse_UNION(char * str);

struct frontend_regexp * Parse_CONCAT(char * str);
 
#endif 