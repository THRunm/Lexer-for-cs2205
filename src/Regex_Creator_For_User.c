#include "Regex_Creator_For_User.h"

int number_of_user = 1;

struct type *user_types = NULL;

struct frontend_regexp **user_fr = NULL;

void initialize_user_types()
{
    number_of_user = 3; // 由用户填写
    // 分配struct type 的内存
    user_types = (struct type *)malloc(number_of_user * sizeof(struct type));

    user_types[0].name = (char *)malloc(50 * sizeof(char));
    strcpy(user_types[0].name, "1"); // 设置第一个字符串值

    user_types[1].name = (char *)malloc(50 * sizeof(char));
    strcpy(user_types[1].name, "2"); // 设置第二个字符串值

    user_types[2].name = (char *)malloc(50 * sizeof(char));
    strcpy(user_types[2].name, "3"); // 设置第三个字符串值

    user_types[0].id = 1;
    user_types[1].id = 2;
    user_types[2].id = 3;
}

void allocate_and_initialize_user_fr()
{
    user_fr = (struct frontend_regexp **)malloc(number_of_user * sizeof(struct frontend_regexp *));

    user_fr[0] = TFr_String("it's");
    user_fr[1] = TFr_String("a");
    user_fr[2] = TFr_String("example");

    return;
} // if