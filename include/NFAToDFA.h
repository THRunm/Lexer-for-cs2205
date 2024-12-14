#ifndef GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H
#define GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H

#include "lang.h"
#include <string.h>
#include <stdbool.h>

// 没写动态数据结构( 用c写这玩意纯属想不开, 没必要) , 若发生错误, 尝试修改以下四个参数

// hash表第一关键字存储最大值, hash表大小
#define HASH_N 999983
#define HASH_M 1000000
// DFA最大边数, 终止点最大个数
#define EDGES_MAX 1000000
#define ENDS_MAX 1000000

struct hash_node{
    int x, s;
    struct hash_node* next;
};

int hash_n, hash_m, hash_c;

struct hash_node** hash_first;
struct hash_node* hash_nodes;

// index只能为0/1
int hash(int index, bool* src, int n) {
    if (index == 0) {
        int h = 114514;
        for (int i = 0; i < n; i ++)
            if (src[i])
                h += (i+998244353)*(i+456)*(i^123456)*(i^547894);
        return ((h % hash_n) + hash_n) % hash_n;
    }
    else {
        int h = 10086;
        for (int i = 0; i < n; i ++)
            if (src[i])
                h += ((i+114514)*(i+45456))^((i^18971554)*(i^66666));
        return h;
    }
}

// 利用双哈希来保证大部分情况下的算法正确性
// 检测点
int detectHash(bool* src, int n) {
    int x = hash(0, src, n), h = hash(1, src, n);
    struct hash_node* i = hash_first[x];
    while (i != NULL && i -> x != h) {
        i = i -> next;
    }
    if (i != NULL)
        return i -> s;
    return -1;
}

// 新增点
void addHash(bool* src, int n) {
    if (hash_c == hash_m) {
        printf("发生错误：hash表预留空间不足，请增大HASH_M");
        return;
    }
    int x = hash(0, src, n), h = hash(1, src, n);
    hash_nodes[hash_c].x = h;
    hash_nodes[hash_c].s = hash_c;
    hash_nodes[hash_c].next = hash_first[x];
    hash_first[x] = hash_nodes + hash_c;
    hash_c ++;
}

// 初始化，n表示hash表大小，m表示容纳数据量
void initialHash(int n, int m) {
    hash_n = n;
    hash_m = m;
    hash_c = 0;
    hash_first = malloc(sizeof (struct hash_node*) * n);
    for (int i = 0; i < n; i ++)
        hash_first[i] = NULL;
    hash_nodes = malloc(sizeof (struct hash_node) * m);
}

// 销毁hash表
void destroyHash() {
    free(hash_first);
    free(hash_nodes);
}

// a 是否在 b 中
bool incs (char a, struct char_set b) {
    for (int i = 0; i < b.n; i ++)
        if (a == b.c[i])
            return true;
    return false;
}

// 复制一个char_set
struct char_set copycs(struct char_set c) {
    struct char_set dst = {malloc(sizeof (char) * c.n), c.n};
    for (int i = 0; i < c.n; i ++)
        dst.c[i] = c.c[i];
    return dst;
}

// 创建一个空的char_set
struct char_set emptycs() {
    struct char_set c = {NULL, 0};
    return c;
}

// 创建一个只有一个字符的char_set
struct char_set solocs(char c) {
    struct char_set cc = {malloc(sizeof(char)), 1};
    cc.c[0] = c;
    return cc;
}

// 输出char_set的结构
void printfcs(struct char_set c) {
    if (c.n == 0)
        printf("episilon");
    for (int i = 0; i < c.n; i ++)
        printf("%c", c.c[i]);
}

// 创建一个含多个字符的char_set
struct char_set mulcs(char* c, int n) {
    struct char_set cc = {malloc(sizeof(char)*n), n};
    for (int i = 0; i < n; i ++)
        cc.c[i] = c[i];
    return cc;
}

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
void addStar(struct star_edges* dst, int u, int v, struct char_set c){
    if (dst -> c == dst -> m) {
        printf("发生错误: 链式前向星预留空间不足");
        return;
    }
    dst -> next[dst -> c] = dst -> first[u];
    dst -> dst[dst -> c] = v;
    dst -> lb[dst -> c] = c;
    dst -> first[u] = dst -> c;
    dst -> c ++;
}

// 找边
int findStar(struct star_edges* dst, int u, int v, char c) {
    for (int i = dst -> first[u]; i != -1; i = dst -> next[i])
        if (dst -> dst[i] == v && incs(c, dst -> lb[i]))
            return i;
    return -1;
}

// 创建新的链式前向星结构体
struct star_edges newStar(int n, int m) {
    struct star_edges a;
    a.n = n;
    a.m = m;
    a.c = 0;
    a.first = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i ++)
        a.first[i] = -1;
    a.dst = malloc(sizeof(int) * m);
    a.next = malloc(sizeof(int) * m);
    a.lb = malloc(sizeof(struct char_set) * m);
    return a;
}

// 析构函数：请务必调用以释放内存
void destroyStar(struct star_edges* a) {
    free(a -> first);
    free(a -> dst);
    free(a -> next);
    for (int i = 0; i < a -> c; i ++)
        free(a -> lb[i].c);
    free(a -> lb);
}

// 输出链式前向星的结构
void printfStar(struct star_edges* a) {
    printf("vertex_num:%d edge_num:%d\n", a -> n, a -> c);
    for (int i = 0; i < a -> n; i ++)
        printf("first #%d: %d\n", i, a -> first[i]);
    for (int i = 0; i < a -> c; i ++) {
        printf("edge #%d: dst %d, next %d, char_set ",i, a -> dst[i], a -> next[i]);
        printfcs(a -> lb[i]);
        printf("\n");
    }
    printf("\n");
}

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
struct finite_automata_exinf newAutomataEx(int n, int maxm, int maxn) {
    struct finite_automata_exinf dst;
    dst.n = n;
    dst.m = 0;
    dst.maxm = maxm;
    dst.maxn = maxn;
    dst.srcc = 0;
    dst.mm = 0;
    //TODO 内存未释放
    dst.src = malloc(sizeof(int) * maxm);
    dst.dst = malloc(sizeof(int) * maxm);
    dst.lb = malloc(sizeof(int) * maxm);
    dst.dstt = malloc(sizeof(int) * maxn);
    return dst;
}

// 加边
void addAutomataEx(int src, int dst, char ch, struct finite_automata_exinf* d) {
    d -> src[d -> m] = src;
    d -> dst[d -> m] = dst;
    d -> lb[d -> m] = solocs(ch);
    d -> m ++;
}

// 加边
void addAutomataExx(int src, int dst, struct char_set ch, struct finite_automata_exinf* d) {
    d -> src[d -> m] = src;
    d -> dst[d -> m] = dst;
    d -> lb[d -> m] = ch;
    d -> m ++;
}

// 析构函数
void destroyAutomataEx(struct finite_automata_exinf* d) {
    free(d -> src);
    free(d -> dst);
    for (int i = 0; i < d -> m; i ++)
        free(d -> lb[i].c);
    free(d -> lb);
    free(d -> dstt);
}

// 输出有限自动机ex的结构
void printfAutomataEx(struct finite_automata_exinf* d) {
    printf("vertex_num:%d edges_num:%d start:%d end_num:%d\n", d -> n, d -> m, d -> srcc, d -> mm);
    for (int i = 0 ; i < d -> m; i ++) {
        printf("edge #%d: %d ~ %d ",i,d -> src[i], d -> dst[i]);
        printfcs(d -> lb[i]);
        printf("\n");
    }
    for (int i = 0; i < d -> mm; i ++)
        printf("end #%d: %d\n", i, d -> dstt[i]);
    printf("\n");
}

// 将[ dst , dst + n ) 赋值为 False
void sbf(bool* dst, int n) {
    for (int i = 0; i < n; i ++)
        dst[i] = false;
}

// 输出一个bool数组
void printfB(bool* dst, int n) {
    for (int i = 0; i < n; i ++)
        printf(dst[i]?"1":"0");
    printf("\n");
}

// 用来更新当前点直接能走到的点有哪些
void search(int current, bool* dst, struct star_edges* c) {
    if (dst[current])
        return;
    dst[current] = true;
    for (int i = c -> first[current]; i != -1; i = c -> next[i]) {
        if (c -> lb[i].n == 0)
            search(c -> dst[i], dst, c);
    }
}

// 寻找下一步的状态有哪些
void nextStep(bool* src, bool* dst, char ch, struct star_edges* c) {
    for (int u = 0; u < c -> n; u ++)
        if (src[u] == 1) {
            for (int i = c -> first[u]; i != -1; i = c -> next[i]) {
                if (incs(ch, c -> lb[i]))
                    search(c -> dst[i], dst, c);
            }
        }
}

// 寻找所有可能的转移
void availableChar(bool* src, bool* avl, struct star_edges* c) {
    for (int u = 0; u < c -> n; u ++)
        if (src[u] == 1) {
            for (int i = c -> first[u]; i != -1; i = c -> next[i]) {
                for (int j = 0; j < c -> lb[i].n; j ++)
                    avl[c -> lb[i].c[j]] = true;
            }
        }
}

// 判断是否包含终止点
int judgeEnding(bool* dst, struct finite_automata_exinf* d) {
    for (int i = 0; i < d -> mm; i ++)
        if (dst[d -> dstt[i]])
            return i;
    return -1;
}

// 暴力建构DFA
void dfsHash(bool* father, char last, bool* src, struct finite_automata_exinf* d, struct star_edges* c, struct finite_automata_exinf* dst,int *types) {
    if (detectHash(src, d -> n) >= 0) {
        if (father != NULL)
            addAutomataEx(detectHash(father, d -> n), detectHash(src, d -> n), last, dst);
        return;
    }
    //printfB(src, d -> n);
    addHash(src, d -> n);
    dst -> n ++;
    if (father != NULL)
        addAutomataEx(detectHash(father, d -> n), detectHash(src, d -> n), last, dst);
    int k;
    if (( k=judgeEnding(src, d))>-1) {
        dst -> dstt[dst -> mm] = dst -> n - 1;
        types[dst -> mm] = k;
        dst -> mm ++;
    }
    bool avl[256];
    sbf(avl, 256);
    availableChar(src, avl, c);
    bool dd[d -> n];
    for (int ch = 0; ch < 256; ch ++)
        if (avl[ch]) {
            sbf(dd, d -> n);
            nextStep(src, dd, ch, c);
            dfsHash(src, ch, dd, d, c, dst,types);
        }
}

// 将NFA转化为链式前向星数组
struct star_edges buildStar (struct finite_automata_exinf* d) {
    struct star_edges dst = newStar(d -> n, EDGES_MAX);
    for (int i = 0; i < d -> m; i ++)
        addStar(&dst, d -> src[i], d -> dst[i], copycs(d -> lb[i]));
    return dst;
}

// 对边进行快排
void sortEx(int l, int r, struct finite_automata_exinf* dst) {
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    int srcm = dst -> src[mid], dstm = dst -> dst[mid];
    int m[3] = {0,0,0};
    int srcc[3][r-l+1], dstt[3][r-l+1];
    struct char_set lbb[3][r-l+1];
    for (int i = l; i < r; i ++) {
        int k = 2;
        if (dst -> src[i] < srcm || (dst -> src[i] == srcm && dst -> dst[i] < dstm ))
            k = 0;
        else if (dst -> src[i] == srcm && dst -> dst[i] == dstm)
            k = 1;
        srcc[k][m[k]] = dst -> src[i];
        dstt[k][m[k]] = dst -> dst[i];
        lbb[k][m[k]] = dst -> lb[i];
        m[k] ++;
    }
    int j = l;
    for (int k = 0; k < 3; k ++)
        for (int i = 0; i < m[k]; i ++) {
            dst -> src[j] = srcc[k][i];
            dst -> dst[j] = dstt[k][i];
            dst -> lb[j] = lbb[k][i];
            j ++;
        }
    sortEx(l, l + m[0], dst);
    sortEx(r - m[2], r, dst);
}

// 将字符进行一个融合操作
void mergeAutomataEx(struct finite_automata_exinf* dst) {
    sortEx(0, dst -> m, dst);
    int m = dst -> m;
    dst -> m = 0;
    int last = 0;
    for (int i = 1; i <= m; i ++) {
        if (i == m || (dst -> src[i] != dst -> src[last] || dst -> dst[i] != dst -> dst[last])) {
            struct char_set ch = {malloc(sizeof(char) * (i - last)), i - last};
            for (int j = last; j < i; j ++) {
                ch.c[j - last] = dst -> lb[j].c[0];
                free(dst -> lb[j].c);
            }
            dst -> src[dst -> m] = dst -> src[last];
            dst -> dst[dst -> m] = dst -> dst[last];
            dst -> lb[dst -> m] = ch;
            dst -> m ++;
            last = i;
        }
    }
}

// 核心功能
struct finite_automata_exinf NFAtoDFA(struct finite_automata_exinf* d,int *types) {
    //printfAutomataEx(d);
    initialHash(HASH_N, HASH_M);
    struct star_edges c = buildStar(d);
    //printfStar(&c);
    bool start[d -> n];
    sbf(start, d -> n);
    search(d -> srcc, start, &c);
    struct finite_automata_exinf ans = newAutomataEx(0, EDGES_MAX, ENDS_MAX);
    dfsHash(NULL, ' ', start, d, &c, &ans, types);
    mergeAutomataEx(&ans);
    destroyStar(&c);
    destroyHash();
    //printfAutomataEx(&ans);
    return ans;
}



// 调用这个!
// 返回一个DFA, 输入NFA个数, 记录NFA存储地址的数组, 各NFA的终止地址, 返回终点个数, 和具体终点是哪些( 需要提前预留足够大小)
struct finite_automata NFA2DFA(int n, struct finite_automata ** nfa, int* dst, int* dst_number, int** ans_dst,int *types,int *num) {
    struct finite_automata_exinf a = newAutomataEx(1, EDGES_MAX, ENDS_MAX);
    a.srcc = 0;
    a.mm = n;
    for (int i = 0; i < n; i ++) {
        addAutomataExx(0, a.n, emptycs(), &a);
        for (int j = 0; j < nfa[i] -> m; j ++)
            addAutomataExx(a.n + nfa[i] -> src[j], a.n + nfa[i] -> dst[j], copycs(nfa[i] -> lb[j]), &a);
        a.dstt[i] = a.n + dst[i];
        a.n += nfa[i] -> n;
    }
    struct finite_automata_exinf ans = NFAtoDFA(&a,types);
    struct finite_automata anss;
    anss.n = ans.n;
    anss.m = ans.m;
    anss.src = ans.src;
    anss.dst = ans.dst;
    anss.lb = ans.lb;
    *dst_number = ans.mm;
    //TODO 请注意这里的内存泄漏有非法写入
    int *count=malloc(sizeof(int)*4096);
    for(int i=0;i<4096;i++)
        count[i]=0;
    for (int i = 0; i < ans.mm; i ++)
        {num[i]=count[types[i]];
        ans_dst[types[i]][count[types[i]]++] = ans.dstt[i];}
    free(ans.dstt);
    free(count);
    destroyAutomataEx(&a);
    return anss;
}
void free_for_dfa(struct finite_automata * dfa) {
    free(dfa -> src);
    free(dfa -> dst);
    for (int i = 0; i < dfa -> m; i ++)
        free(dfa -> lb[i].c);
    free(dfa -> lb);
}


#endif //GRAMMAR_PARSER_FOR_CS2205_NFATODFA_H