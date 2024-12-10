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

    struct char_set *set1 = (struct char_set *)malloc(sizeof(struct char_set));
    set1->c = strdup("abc");
    set1->n = strlen(set1->c);

    test_fr_1[0] = TFr_Union(
        TFr_Concat(
            TFr_CharSet(set1),
            TFr_SingleChar('d')
        ),
        TFr_Plus(TFr_SingleChar('e'))
    );

}