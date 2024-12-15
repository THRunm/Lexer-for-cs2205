# 程序语言编程任务报告

尊敬的曹老师和助教们，你们好。本文是王艺润、张珂玮、裘凯希、车昕宇小组的编程任务最终报告，我们的主题是《词法分析器，根据正则表达式生成 DFA 》。

本报告将简述本项目实现的特性，具体内容的组织，各部分的实现，以及编译使用及测试方法。

本项目托管于 [THRunm/Lexer-for-cs2205](https://github.com/THRunm/Lexer-for-cs2205) 。

**由于本项目在 linux 环境下运行，请保证您要进行词法分析的目标文档的换行符为 LF 而非 CRLF 。**

## 特性

* 本项目实现了一个简单的词法分析器。其接受解析树形式的正则表达式，并依次处理出简化正则表达式、NFA 和 DFA 。最后，分析器依据 DFA 将输入的字符串转化为分段结果与分类结果。

  我们的词法分析器支持按照 ”匹配字符串长度第一优先“ 、“匹配规则先后次序第二优先” 的方式进行词法分析。即，若同一字符串同时被多个词法规则接受，则优先选择匹配长度更长者；若同时存在多个匹配长度最长的词法规则，则优先选择最先定义者。

  本项目通过较为精细的实现保证了内存安全性。

## 组织

* 本项目的组织如下：

  ```bash
  .
  ├── CMakeLists.txt
  ├── figure
  │   └── process.png
  ├── include
  │   ├── DFALexicalAnalyzer.h
  │   ├── NFAToDFA.h
  │   ├── RegexToNFA.h
  │   ├── Regex_Creator_For_User.h
  │   ├── SimplifyRegex.h
  │   └── lang.h
  ├── readme.md
  ├── release
  │   └── main
  ├── src
  │   ├── DFALexicalAnalyzer.c
  │   ├── NFAToDFA.c
  │   ├── RegexToNFA.c
  │   ├── Regex_Creator_For_User.c
  │   ├── SimplifyRegex.c
  │   ├── lang.c
  │   ├── main.c
  │   └── read_files
  │       ├── read_file1
  │       ├── read_file10
  │       ├── read_file2
  │       ├── read_file3
  │       ├── read_file4
  │       ├── read_file5
  │       ├── read_file6
  │       ├── read_file7
  │       ├── read_file8
  │       └── read_file9
  └── test
      ├── compare_struct.c
      ├── compare_struct.h
      ├── test.c
      └── test.h
  ```
  
  本项目使用 CMake 在 linux 环境下编译  。`include` 文件夹用于存放项目各部分的头文件。`src` 文件夹用于存放项目各部分的源代码，其中 `read_files` 文件夹用于存放我们提供的样例（即输入进行词法分析的字符串），分别作为 `text.c` 中包含的 10 个测试点对应的待匹配文本串。`test` 文件夹则单独存放了测试文件，包括比较器、以及用于生成测试数据（即描述词法规则的正则表达式）的测试器。`figure` 文件夹存放了 `readme.md` 中的图片。`release` 文件夹中则存放了本项目编译完成的可执行文件。 

## 实现

![](https://cdn.luogu.com.cn/upload/image_hosting/rfn7045w.png)

* `lang.c/.h` 由课程提供，实现了用于存储本项目所需数据结构的结构体。

* 本项目的词法分析器分为四部分实现。以下我们将简述各部分的实现。
  1. `SimplifyRegex.c/.h` 将输入的解析树形式的正则表达式转化为简化正则表达式。其中，输入的正则表达式可能包含：字符集、可选的情形、循环、至少一次的循环、字符串、单字符、并集以及连接。转化得到的简化正则表达式则只包含：字符集、空字符串、循环（即 `*` ）、并集以及连接。
  2. `RegexToNFA.c/.h` 将描述词法结构的每一个简化正则表达式转化为 NFA 。本部分按照 [Lexer.pdf](https://jhc.sjtu.edu.cn/public/courses/CS2205/Lexer.pdf) 中给出的规则构建 NFA 。
  3. `NFAToDFA.c/.h` 将一组 NFA 转化为一个 DFA 。我们使用一个统一的起始点，向所有 NFA 的起始点连边，并基于考虑 NFA 中所有当前可能处于的状态的集合的方法，构建 DFA 。此 DFA 接受满足给出的词法规则的全部字符串。而为了保证 “匹配规则先后次序第二优先” ，我们令 DFA 中的每个终止节点均只保存此节点对应的最先定义的词法规则。
  4. `SimplifyRegex.c` 依据 DFA 将输入的字符串转化为分段结果和分类结果。我们首先基于上一步得到的 DFA 预处理出状态转移表。接下来，对于每一个输入的字符串，我们根据状态转移表对其进行匹配，以得到对应的分段结果和分类结果。特别的，为了保证 ”匹配字符串长度第一优先“ ，我们的策略是，匹配当前字符串中尽量多的字符，直到字符串结束或者失配为止；接下来，找到最后一个到达的终止状态，选择此状态保存的类型作为当前的分类结果。
  
* `main.c` 文件的实现。`main.c` 文件接受两个参数 `test_case` 以及 `read_file` ，前者表示提供词法规则定义的测试点的编号，后者表示要进行词法分析的目标文档的地址。`main.c` 按顺序组合了词法分析器的四个组件，按照词法规则分析目标文档，最后释放所有内存，以保证内存安全性。

  `main.c` 的输出遵从以下格式：

  ```bash
  types_num:                  # The number of given types.
  ac                          # Each type is listed in order.
  [a][c]
  ...        			
  nfa started                 # Begin to print nfa of each type.
  start:0,end:3               # The start and end vertices.
  n = 4, m = 3                # The number of vertices and edges.
  src = 0, dst = 1, lb = a    # Description of each edge.
  ...
  nfa finished                # Finish printinf nfas.
  n = 23, m = 53              # Begin to print the only dfa.
  src = 0, dst = 1, lb = a    # Description of each edge.
  ...
  dfa finished                # Finish printing dfa.
  Line Number 2               # The number of lines of the given doc.
  Tokens:                     # This is printed each line.
  Token:"ac", Type: ac        # The Segmentation and classification results.
  ...
  tokens finished             # Finish printing tokens.
  ```

* 测试文件的实现。本项目的测试文件分为两部分，第一部分 `compare_struct.c/.h` 是比较器，用于对比字符集、正则表达式、简化正则表达式与有限状态自动机。第二部分 `test.c/.h` 是测试器，共包含了 10 个测试点，每个测试点所定义的词法规则各有侧重，如下所述：

  | 编号 | 测试点                                                       |
  | ---- | ------------------------------------------------------------ |
  | 1    | 定义了 if 词法规则。                                         |
  | 2    | 定义了实数词法规则。                                         |
  | 3    | 定义了变量名词法规则。                                       |
  | 4    | 定义了赋值运算词法规则。                                     |
  | 5    | 定义了简化的 `for` 循环词法规则。                            |
  | 6    | 定义了简化的 `while` 和 `do-while` 循环词法规则。            |
  | 7    | 用于测试 “匹配规则先后次序优先” 的正确性。其中的词法规则包括 `abc*` 、`abd*` 与 `abe*` ，对应的 `read_file7` 中的文本串则为 `"ab"` ，其正确的匹配了类型 `abc*` 。 |
  | 8    | 用于测试 ”匹配字符串长度第一优先“ ，“匹配规则先后次序第二优先” 的正确性。其中定义的词法规则依次为 `ab` 、`abb` 与 `ab*` ，对应的 `read_file8` 中的文本串则为 `"abbbbbbbb\nabbbbb\nabbbbbbbbbbbb"` ，它们均正确的匹配了类型 `ab*` 。 |
  | 9    | 用于测试 ”匹配字符串长度第一优先“ ，“匹配规则先后次序第二优先” 的正确性。其中定义的词法规则依次为 `ac` 、`ace` 、`a+b*c+d*e+f*` 、`a*c*e*` 与 `(a|b)(c|d)(e|f)` ，对应的 `read_file9` 中的文本串则为 `"ac\nace"` ，它们分别正确的匹配了类型 `ac` 与 `ace` 。 |
  | 10   | 其中这里定义了一套简单的 C 语言词法规则。                    |

* 用户自定义描述词法规则 `Regex_Creator_For_User.c/.h` 的实现。其中包含了简要的使用说明以及一个例子。

## 编译使用以及测试方法

* 编译方法：
  1. 请在本项目根目录下创建 `build` 文件夹以存放编译文件，并进入该文件夹。
  
     ```bash
     mkdir build
     cd build
     ```
  
  2. 在 `build` 文件夹中打开 linux 终端，依次输入 `cmake ..` 和 `make` 以编译生成可执行文件。
  
     ```bash
     cmake ..
     make
     ```
  
* 测试方法：编译完成后，直接运行 `main` 可执行文件即可。运行 `main` 的命令为 `./main <test_case>` 。其中 `<test_case>` 为测试点编号，应当为一个 1 到 10 之间的整数。
  
  ```bash
  ./main <test_case>
  ```
  
* 使用方法：我们在 `Regex_Creator_For_User.c` 中为用户提供了自定义词法分析规则的接口。具体的，您需要在 `initialize_user_types()` 函数中填写自定义词法规则的个数、类型名，并从 1 开始依次填写它们的 id 值。您还需要在 `allocate_and_initialize_user_fr()` 函数中填写每一个词法规则的解析树形式的正则表达式（您可能会用到 `lang.h` 中定义的用于构建解析树的函数）。

  调用自定义词法分析器的命令为 `./main -1 <read_file>` ，其中 `<read_file>` 为您希望进行词法分析的目标文档的地址。
  
  ```bash
  ./main -1 <read_file>
  ```