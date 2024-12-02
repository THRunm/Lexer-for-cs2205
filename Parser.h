#include "lang.h"

#ifndef PARSER_H
#define PARSER_H
 
struct frontend_regexp * string_to_frontend_regexp(char ** str); // convert a string to a frontend regexp 

struct frontend_regexp * Parser(char * str);
 
#endif 