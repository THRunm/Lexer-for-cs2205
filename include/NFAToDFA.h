#ifndef GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H
#define GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H

#include "lang.h"
#include <string.h>
#include <stdbool.h>




struct hash_node{
    int x, s;
    struct hash_node* next;
};


// index只能为0/1
int hash(int index, bool* src, int n) ;

int detectHash(bool* src, int n) ;

// 新增点
void addHash(bool* src, int n) ;

// 初始化，n表示hash表大小，m表示容纳数据量
void initialHash(int n, int m) ;

// 销毁hash表
void destroyHash() ;

// a 是否在 b 中
bool incs (char a, struct char_set b) ;

// 复制一个char_set
struct char_set copycs(struct char_set c);

// 创建一个空的char_set
struct char_set emptycs() ;

// 创建一个只有一个字符的char_set
struct char_set solocs(char c) ;

// 输出char_set的结构
void printfcs(struct char_set c);

// 创建一个含多个字符的char_set
struct char_set mulcs(char* c, int n) ;

// 链式前向星
struct star_edges {
    // n个点, m条边, 已经存了c条边
    int n,m,c;
    int* first;
    int* dst;
    struct char_set* lb;
    int* next;
};

// 加边, 此处的char_set需要保证是个unique_ptr
void addStar(struct star_edges* dst, int u, int v, struct char_set c);

// 找边
int findStar(struct star_edges* dst, int u, int v, char c) ;

// 创建新的链式前向星结构体
struct star_edges newStar(int n, int m) ;

// 析构函数：请务必调用以释放内存
void destroyStar(struct star_edges* a);

// 输出链式前向星的结构
void printfStar(struct star_edges* a) ;

// 有限自动机ex, 额外记录了起点、终点和最大可存储边数
struct finite_automata_exinf {
    int n;
    int m;
    int * src;
    int * dst;
    struct char_set * lb; // 这五个定义与finite_automata相同
    int srcc; // 起始点编号
    int mm; // 终止点个数
    int* dstt; // 终止点编号
    int maxm; // 可容纳边数
    int maxn; // 可容纳终止点个数
};

// 创建新的有限自动机ex
struct finite_automata_exinf newAutomataEx(int n, int maxm, int maxn);

// 加边
void addAutomataEx(int src, int dst, char ch, struct finite_automata_exinf* d) ;

// 加边
void addAutomataExx(int src, int dst, struct char_set ch, struct finite_automata_exinf* d) ;

// 析构函数
void destroyAutomataEx(struct finite_automata_exinf* d);

// 输出有限自动机ex的结构
void printfAutomataEx(struct finite_automata_exinf* d) ;

// 将[ dst , dst + n ) 赋值为 False
void sbf(bool* dst, int n);
// 输出一个bool数组
void printfB(bool* dst, int n) ;

// 用来更新当前点直接能走到的点有哪些
void search(int current, bool* dst, struct star_edges* c);

// 寻找下一步的状态有哪些
void nextStep(bool* src, bool* dst, char ch, struct star_edges* c) ;

// 寻找所有可能的转移
void availableChar(bool* src, bool* avl, struct star_edges* c);

// 判断是否包含终止点
int judgeEnding(bool* dst, struct finite_automata_exinf* d) ;

// 暴力建构DFA
void dfsHash(bool* father, char last, bool* src, struct finite_automata_exinf* d, struct star_edges* c, struct finite_automata_exinf* dst,int *types) ;

// 将NFA转化为链式前向星数组
struct star_edges buildStar (struct finite_automata_exinf* d) ;

// 对边进行快排
void sortEx(int l, int r, struct finite_automata_exinf* dst);

// 将字符进行一个融合操作
void mergeAutomataEx(struct finite_automata_exinf* dst) ;

// 核心功能
struct finite_automata_exinf NFAtoDFA(struct finite_automata_exinf* d,int *types);



// 调用这个!
// 返回一个DFA, 输入NFA个数, 记录NFA存储地址的数组, 各NFA的终止地址, 返回终点个数, 和具体终点是哪些( 需要提前预留足够大小)
struct finite_automata *NFA2DFA(int n, struct finite_automata ** nfa, int* dst, int* dst_number, int** ans_dst,int *types,int *num);
void free_for_dfa(struct finite_automata * dfa);


#endif //GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H