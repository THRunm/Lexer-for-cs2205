//
// Created by asus on 24-12-10.
//
#include "test.h"

int number_of_test = 1;

struct type *test_types = NULL;

struct frontend_regexp **test_fr = NULL;

void initialize_test_types_1(){
  number_of_test = 1;
  // 分配struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type)*2);

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *)*2);

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 1;
}
void initialize_test_types_2(){
  // 分配 2 个 struct type 的内存
  number_of_test = 1;
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "RealNumber"); // 设置第一个字符串值

  test_types->id = 2;
}
void initialize_test_types_3(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_4(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_5(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_6(){
  // 分配 2 个 struct type 的内存
  number_of_test = 2;
  test_types = (struct type *)malloc(sizeof(struct type)*2);

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "while"); // 设置第一个字符串值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "do_while"); // 设置第一个字符串值
  test_types->id = 24;
}
void initialize_test_types_7(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_8(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_9(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}
void initialize_test_types_10(){
  // 分配 2 个 struct type 的内存
  test_types = (struct type *)malloc(sizeof(struct type));

  // 分配第一个 name 指针的内存，存储 2 个字符串的指针
  test_types->name = (char **)malloc(sizeof(char *));

  // 分配每个字符串的空间，并赋值
  test_types->name[0] = (char *)malloc(50 * sizeof(char));
  strcpy(test_types->name[0], "If"); // 设置第一个字符串值

  test_types->id = 24;
}

void initialize_test_types(int test_case)
{
   switch(test_case) {
      case 1:
         initialize_test_types_1();
         break;
      case 2:
         initialize_test_types_2();
         break;
      case 3:
         initialize_test_types_3();
         break;
      case 4:
         initialize_test_types_4();
         break;
      case 5:
         initialize_test_types_5();
         break;
      case 6:
         initialize_test_types_6();
         break;
      case 7:
         initialize_test_types_7();
         break;
      case 8:
         initialize_test_types_8();
         break;
      case 9:
         initialize_test_types_9();
         break;
      case 10:
         initialize_test_types_10();
         break;
   }
}

void allocate_and_initialize_test_fr_1(){
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
}// if

void allocate_and_initialize_test_fr_2() {
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));

   // 第一步：创建实数正则表达式的各个组成部分

   // 单独的零："0"
   struct frontend_regexp *single_zero = TFr_SingleChar('0');

   // 非零数字集合：[1-9]
   struct char_set *nonzero_digit_set = malloc(sizeof(struct char_set));
   nonzero_digit_set->c = strdup("123456789");
   nonzero_digit_set->n = strlen(nonzero_digit_set->c);
   struct frontend_regexp *nonzero_digit = TFr_CharSet(nonzero_digit_set);

   // 数字集合：[0-9]
   struct char_set *digit_set = malloc(sizeof(struct char_set));
   digit_set->c = strdup("0123456789");
   digit_set->n = strlen(digit_set->c);
   struct frontend_regexp *digit = TFr_CharSet(digit_set);

   // 非零开头的多位数字：[1-9][0-9]*
   struct frontend_regexp *nonzero_integer_part =
       TFr_Concat(nonzero_digit, TFr_Star(digit));

   // 整数部分：( "0" | [1-9][0-9]* )
   struct frontend_regexp *integer_part =
       TFr_Union(single_zero, nonzero_integer_part);

   // 小数点："."
   struct frontend_regexp *decimal_point = TFr_SingleChar('.');

   // 小数部分：[0-9]*
   struct frontend_regexp *fractional_part = TFr_Star(digit);

   // 可选小数部分：( "." [0-9]* )?
   struct frontend_regexp *optional_fractional_part =
       TFr_Option(TFr_Concat(decimal_point, fractional_part));

   // 可选符号：[+|-]?
   struct char_set *sign_set = malloc(sizeof(struct char_set));
   sign_set->c = strdup("+-");
   sign_set->n = strlen(sign_set->c);
   struct frontend_regexp *sign = TFr_Option(TFr_CharSet(sign_set));

   // 科学计数部分：( "e" [+|-]? [0-9]+ )?
   struct frontend_regexp *exp_symbol = TFr_SingleChar('e');
   struct frontend_regexp *exp_part =
       TFr_Option(TFr_Concat(exp_symbol, TFr_Concat(sign, TFr_Plus(digit))));

   // 完整正则表达式：[+|-]? ( "0" | [1-9][0-9]* ) ("."[0-9]*)? ("e"[+|-]?[0-9]+)?
   test_fr[0]= TFr_Concat(
       sign, TFr_Concat(integer_part,
                        TFr_Concat(optional_fractional_part, exp_part)));
}// real number

void allocate_and_initialize_test_fr_3(){
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
   // 第一步：创建变量名的正则表达式各个部分

   // 字母集合：[a-zA-Z]
   struct char_set *letter_set = malloc(sizeof(struct char_set));
   letter_set->c = strdup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
   letter_set->n = strlen(letter_set->c);
   struct frontend_regexp *letter = TFr_CharSet(letter_set);

   // 数字集合：[0-9]
   struct char_set *digit_set = malloc(sizeof(struct char_set));
   digit_set->c = strdup("0123456789");
   digit_set->n = strlen(digit_set->c);
   struct frontend_regexp *digit = TFr_CharSet(digit_set);

   // 下划线："_"
   struct frontend_regexp *underscore = TFr_SingleChar('_');

   // 变量名的首字符：( [a-zA-Z] | "_" )
   struct frontend_regexp *first_char = TFr_Union(letter, underscore);

   // 变量名的后续字符：( [a-zA-Z] | "_" | [0-9] )
   struct frontend_regexp *other_char = TFr_Union(
       TFr_Union(letter, underscore),
       digit
   );

   // 后续字符零个或多个：( [a-zA-Z] | "_" | [0-9] )*
   struct frontend_regexp *other_chars = TFr_Star(other_char);

   // 完整的变量名正则表达式：( ( [a-zA-Z] | "_" ) ( [a-zA-Z] | "_" | [0-9] )* )
   test_fr[0] = TFr_Concat(first_char, other_chars);
}// variable name

void allocate_and_initialize_test_fr_4(){
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
   // 构造表示赋值运算符的正则表达式

   // 单个字符赋值运算符："="
   struct frontend_regexp *assign_op = TFr_SingleChar('=');

   // 复合赋值运算符

   // 加赋值："+="
   struct frontend_regexp *plus = TFr_SingleChar('+');
   struct frontend_regexp *plus_assign = TFr_Concat(plus, assign_op);

   // 减赋值："-="
   struct frontend_regexp *minus = TFr_SingleChar('-');
   struct frontend_regexp *minus_assign = TFr_Concat(minus, assign_op);

   // 乘赋值："*="
   struct frontend_regexp *multiply = TFr_SingleChar('*');
   struct frontend_regexp *multiply_assign = TFr_Concat(multiply, assign_op);

   // 除赋值："/="
   struct frontend_regexp *divide = TFr_SingleChar('/');
   struct frontend_regexp *divide_assign = TFr_Concat(divide, assign_op);

   // 位与赋值："&="
   struct frontend_regexp *bitwise_and = TFr_SingleChar('&');
   struct frontend_regexp *bitwise_and_assign = TFr_Concat(bitwise_and, assign_op);

   // 所有赋值运算符的联合
   test_fr[0] = TFr_Union(
       assign_op,
       TFr_Union(
           plus_assign,
           TFr_Union(
               minus_assign,
               TFr_Union(multiply_assign, TFr_Union(divide_assign, bitwise_and_assign))
                   )
               )
   );
}// assignment operators

void allocate_and_initialize_test_fr_5(){
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
   // 第一步：构造表示C语言中for循环的正则表达式

   // "for" 关键字
   struct frontend_regexp *keyword_for = TFr_String("for");

   // 空格和制表符集合：[ \t\n]*（可选空格或制表符）
   struct char_set *whitespace_set = malloc(sizeof(struct char_set));
   whitespace_set->c = strdup(" \t\n");
   whitespace_set->n = strlen(whitespace_set->c);
   struct frontend_regexp *whitespace = TFr_Star(TFr_CharSet(whitespace_set));

   // 小括号："(" 和 ")"
   struct frontend_regexp *open_paren = TFr_SingleChar('(');
   struct frontend_regexp *close_paren = TFr_SingleChar(')');

   // 分号：";"
   struct frontend_regexp *semicolon = TFr_SingleChar(';');

   // 变量名：以字母开头，后面跟字母或数字
   struct char_set *alpha_set = malloc(sizeof(struct char_set));
   alpha_set->c = strdup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
   alpha_set->n = strlen(alpha_set->c);
   struct frontend_regexp *alpha = TFr_CharSet(alpha_set);

   struct char_set *alnum_set = malloc(sizeof(struct char_set));
   alnum_set->c = strdup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
   alnum_set->n = strlen(alnum_set->c);
   struct frontend_regexp *alnum = TFr_Star(TFr_CharSet(alnum_set));

   struct frontend_regexp *variable = TFr_Concat(alpha, alnum);

   // 整数部分（不允许前导零）：( "0" | [1-9][0-9]* )
   struct frontend_regexp *single_zero = TFr_SingleChar('0');
   struct frontend_regexp *nonzero_digit = TFr_CharSet(&(struct char_set){"123456789", 9});
   struct frontend_regexp *nonzero_integer = TFr_Concat(nonzero_digit, TFr_Star(TFr_CharSet(&(struct char_set){"0123456789", 10})));
   struct frontend_regexp *integer = TFr_Union(single_zero, nonzero_integer);

   // 赋值语句：变量 = 整数
   struct frontend_regexp *equal_sign = TFr_SingleChar('=');
   struct frontend_regexp *assignment = TFr_Concat(variable, TFr_Concat(equal_sign, integer));

   // 条件表达式：变量 < 整数
   struct frontend_regexp *less_than = TFr_SingleChar('<');
   struct frontend_regexp *condition = TFr_Concat(variable, TFr_Concat(less_than, integer));

   // 增量表达式：变量++
   struct frontend_regexp *plus = TFr_SingleChar('+');
   struct frontend_regexp *increment = TFr_Concat(variable, TFr_Concat(plus, plus));

   // for 循环完整格式：
   // for ( assignment ; condition ; increment )
   test_fr[0] = TFr_Concat(
       keyword_for,
       TFr_Concat(
           whitespace,
           TFr_Concat(
               open_paren,
               TFr_Concat(
                   whitespace,
                   TFr_Concat(
                       assignment,
                       TFr_Concat(
                           whitespace,
                           TFr_Concat(
                               semicolon,
                               TFr_Concat(
                                   whitespace,
                                   TFr_Concat(
                                       condition,
                                       TFr_Concat(
                                           whitespace,
                                           TFr_Concat(
                                               semicolon,
                                               TFr_Concat(
                                                   whitespace,
                                                   TFr_Concat(increment, TFr_Concat(whitespace, close_paren))
                                                       )
                                                   )
                                               )
                                           )
                                       )
                                   )
                               )
                           )
                       )
                   )
               )
   );
}// simple for loop

void allocate_and_initialize_test_fr_6() {
   test_fr = (struct frontend_regexp **)malloc(2 * sizeof(struct frontend_regexp *));

   // while loop: "while (<cond>) { <body> }"
   struct frontend_regexp *while_keyword = TFr_String("while");
   struct frontend_regexp *open_paren = TFr_SingleChar('(');
   struct frontend_regexp *cond = TFr_CharSet(&(struct char_set){ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!&|=<>+-*/%", 80 });
   struct frontend_regexp *close_paren = TFr_SingleChar(')');
   struct frontend_regexp *open_brace = TFr_SingleChar('{');
   struct frontend_regexp *body = TFr_CharSet(&(struct char_set){ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789; \\t\\n", 60 });
   struct frontend_regexp *close_brace = TFr_SingleChar('}');

   test_fr[0] = TFr_Concat(
       while_keyword,
       TFr_Concat(
           open_paren,
           TFr_Concat(
               cond,
               TFr_Concat(
                   close_paren,
                   TFr_Concat(
                       open_brace,
                       TFr_Concat(body, close_brace))))));

   // do-while loop: "do { <body> } while (<cond>);"
   struct frontend_regexp *do_keyword = TFr_String("do");
   struct frontend_regexp *semicolon = TFr_SingleChar(';');

   test_fr[1] = TFr_Concat(
       do_keyword,
       TFr_Concat(
           open_brace,
           TFr_Concat(
               body,
               TFr_Concat(
                   close_brace,
                   TFr_Concat(
                       while_keyword,
                       TFr_Concat(
                           open_paren,
                           TFr_Concat(cond, TFr_Concat(close_paren, semicolon))))))));
}//simple while and do-while loop

void allocate_and_initialize_test_fr_7(){
   test_fr = (struct frontend_regexp **)malloc(3 * sizeof(struct frontend_regexp *));
}

void allocate_and_initialize_test_fr_8(){
   test_fr = (struct frontend_regexp **)malloc(3 * sizeof(struct frontend_regexp *));
}

void allocate_and_initialize_test_fr_9(){
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
}

void allocate_and_initialize_test_fr_10(){
   test_fr = (struct frontend_regexp **)malloc(1 * sizeof(struct frontend_regexp *));
}

void allocate_and_initialize_test_fr(int test_case) {
   switch (test_case) {
   case 1:
         allocate_and_initialize_test_fr_1();
         break;
   case 2:
         allocate_and_initialize_test_fr_2();
         break;
   case 3:
         allocate_and_initialize_test_fr_3();
         break;
   case 4:
         allocate_and_initialize_test_fr_4();
         break;
   case 5:
         allocate_and_initialize_test_fr_5();
         break;
   case 6:
         allocate_and_initialize_test_fr_6();
         break;
   case 7:
         allocate_and_initialize_test_fr_7();
         break;
   case 8:
         allocate_and_initialize_test_fr_8();
         break;
   case 9:
         allocate_and_initialize_test_fr_9();
         break;
   case 10:
         allocate_and_initialize_test_fr_10();
         break;
   }
}