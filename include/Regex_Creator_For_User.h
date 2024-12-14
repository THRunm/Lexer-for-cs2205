#include "lang.h"
#include "../include/DFALexicalAnalyzer.h"

#ifndef GRAMMAR_PARSER_FOR_CS2205_REGEXPARSER_H
#define GRAMMAR_PARSER_FOR_CS2205_REGEXPARSER_H

extern int number_of_user;

extern struct type * user_types;

extern struct frontend_regexp ** user_fr;

void initialize_user_types();

void allocate_and_initialize_user_fr();
#endif //GRAMMAR_PARSER_FOR_CS2205_REGEXTONFA_H