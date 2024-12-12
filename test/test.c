//
// Created by asus on 24-12-10.
//
#include "test.h"

int number_of_test = 1;

struct type *test_types = NULL;

struct frontend_regexp **test_fr = NULL;

void initialize_test_types()
{
    // 分配 2 个 struct type 的内存
    test_types = (struct type *)malloc(sizeof(struct type));

    // 分配第一个 name 指针的内存，存储 2 个字符串的指针
    test_types->name = (char **)malloc(sizeof(char *));

    // 分配每个字符串的空间，并赋值
    test_types->name[0] = (char *)malloc(50 * sizeof(char));
    strcpy(test_types->name[0], "If"); // 设置第一个字符串值

    test_types->id = 24;
}

void allocate_and_initialize_test_fr()
{
    test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
    struct char_set whitespace = {" \t", 2}; // \s: space and tab
    struct char_set non_rparen = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*-_=+[]{}|;:',.<>?/`~ ", 95};

    struct frontend_regexp *if_keyword = TFr_String("if");
    struct frontend_regexp *optional_whitespace = TFr_Star(TFr_CharSet(&whitespace));
    struct frontend_regexp *left_paren = TFr_SingleChar('(');
    struct frontend_regexp *condition = TFr_Star(TFr_CharSet(&non_rparen));
    struct frontend_regexp *right_paren = TFr_SingleChar(')');
    struct frontend_regexp *left_brace = TFr_SingleChar('{');
    struct frontend_regexp *body = TFr_Star(TFr_CharSet(&non_rparen));
    struct frontend_regexp *right_brace = TFr_SingleChar('}');

    test_fr[0] =
        TFr_Concat(if_keyword,
                   TFr_Concat(optional_whitespace,
                              TFr_Concat(left_paren,
                                         TFr_Concat(condition,
                                                    TFr_Concat(right_paren,
                                                               TFr_Concat(optional_whitespace,
                                                                          TFr_Concat(left_brace,
                                                                                     TFr_Concat(body,
                                                                                                right_brace))))))));
    
    return;
}