//
// Created by asus on 24-12-10.
//
#include "test.h"

int number_of_test1 = 1;

struct type * test_types_1 = NULL;

struct frontend_regexp ** test_fr_1 = NULL;


void initialize_test1_types() {
    // 分配 2 个 struct type 的内存
    test_types_1 = (struct type *)malloc(sizeof(struct type));
    
    // 分配第一个 name 指针的内存，存储 2 个字符串的指针
    test_types_1->name = (char **)malloc(sizeof(char *));
    
    // 分配每个字符串的空间，并赋值
    test_types_1->name[0] = (char *)malloc(50 * sizeof(char));
    strcpy(test_types_1->name[0], "MambaOut"); // 设置第一个字符串值

    test_types_1->id = 24; 
}


void allocate_and_initialize_test_fr_1() {
    test_fr_1 = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));

    struct frontend_regexp * r_i = TFr_SingleChar('i');
    struct frontend_regexp * r_f = TFr_SingleChar('f');
    struct frontend_regexp * r_if = TFr_Concat(r_i, r_f);

    // Construct whitespace (space or tab)
    struct char_set ws_chars = { " \t", 2 };
    struct frontend_regexp * r_ws = TFr_CharSet(&ws_chars);

    // Construct "("
    struct frontend_regexp * r_lparen = TFr_SingleChar('(');

    // Construct any characters except ")"
    struct char_set not_rparen = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_ ", 63 };
    struct frontend_regexp * r_not_rparen = TFr_CharSet(&not_rparen);
    struct frontend_regexp * r_cond = TFr_Star(r_not_rparen);

    // Construct ")"
    struct frontend_regexp * r_rparen = TFr_SingleChar(')');

    // Construct "{"
    struct frontend_regexp * r_lbrace = TFr_SingleChar('{');

    // Construct any characters except "}"
    struct char_set not_rbrace = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_ ", 63 };
    struct frontend_regexp * r_not_rbrace = TFr_CharSet(&not_rbrace);
    struct frontend_regexp * r_body = TFr_Star(r_not_rbrace);

    // Construct "}"
    struct frontend_regexp * r_rbrace = TFr_SingleChar('}');

    // Concatenate parts: "if" + ws + "(" + condition + ")" + ws + "{" + body + "}"
    struct frontend_regexp * concat1 = TFr_Concat(r_if, r_ws);
    struct frontend_regexp * concat2 = TFr_Concat(concat1, r_lparen);
    struct frontend_regexp * concat3 = TFr_Concat(concat2, r_cond);
    struct frontend_regexp * concat4 = TFr_Concat(concat3, r_rparen);
    struct frontend_regexp * concat5 = TFr_Concat(concat4, r_ws);
    struct frontend_regexp * concat6 = TFr_Concat(concat5, r_lbrace);
    struct frontend_regexp * concat7 = TFr_Concat(concat6, r_body);
    test_fr_1[0] = TFr_Concat(concat7, r_rbrace);
}