#include "Regex_Creator_For_User.h"

int number_of_user = 1;

struct type *user_types = NULL;

struct frontend_regexp **user_fr = NULL;

void initialize_user_types()
{
    number_of_user = 1;
    // 分配struct type 的内存
    user_types = (struct type *)malloc(sizeof(struct type));

    user_types[0].name = (char *)malloc(50 * sizeof(char));
    strcpy(user_types[0].name, "If"); // 设置第一个字符串值

    user_types[0].id = 1;
}

void allocate_and_initialize_user_fr()
{
    user_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
    struct char_set whitespace = {" \t", 2}; // \s: space and tab
    struct char_set non_rparen = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*-_=+[]{}|;:',.<>?/`~ ()", 95};
    struct char_set no_rparen = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*-_=+[]{}|;:',.<>?/`~ ()", 95};

    struct frontend_regexp *if_keyword = TFr_String("if");
    struct frontend_regexp *optional_whitespace = TFr_Star(TFr_CharSet(&whitespace));
    struct frontend_regexp *left_paren = TFr_SingleChar('(');
    struct frontend_regexp *condition = TFr_Star(TFr_CharSet(&no_rparen));
    struct frontend_regexp *right_paren = TFr_SingleChar(')');
    struct frontend_regexp *left_brace = TFr_SingleChar('{');
    struct frontend_regexp *body = TFr_Star(TFr_CharSet(&non_rparen));
    struct frontend_regexp *right_brace = TFr_SingleChar('}');

    user_fr[0] =
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
} // if