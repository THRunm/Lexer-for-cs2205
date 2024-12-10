cmake_minimum_required(VERSION 3.16)

# 项目名称
project(GRAMMAR_PARSER_FOR_CS2205 C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)

# 包含目录
include_directories(include)

# 源文件
file(GLOB SRC_FILES src/*.c)

# 添加主可执行文件
add_executable(main ${SRC_FILES})


# 添加测试任务的目标
#add_executable(test_task1 test/test_task1/test_task1.c ${SRC_FILES})
#add_executable(test_task2 test/test_task2/test_task2.c ${SRC_FILES})
#add_executable(test_task3 test/test_task3/test_task3.c ${SRC_FILES})
#add_executable(test_task4 test/test_task4/test_task4.c ${SRC_FILES})

# 链接测试目标和需要的头文件
#target_include_directories(test_task1 PRIVATE include test/test_task1)
#target_include_directories(test_task2 PRIVATE include test/test_task2)
#target_include_directories(test_task3 PRIVATE include test/test_task3)
#target_include_directories(test_task4 PRIVATE include test/test_task4)

# 启用测试
#enable_testing()

# 添加测试
#add_test(NAME TestTask1 COMMAND test_task1)
#add_test(NAME TestTask2 COMMAND test_task2)
#add_test(NAME TestTask3 COMMAND test_task3)
#add_test(NAME TestTask4 COMMAND test_task4)
###