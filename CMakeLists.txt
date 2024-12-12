cmake_minimum_required(VERSION 3.10)
project(RegexProject)

# 设置C标准
set(CMAKE_C_STANDARD 11)

# 收集源文件(除了main.c)
file(GLOB_RECURSE LIB_SOURCES 
    "src/*.c"
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/main.c")

# 收集测试辅助文件
#set(TEST_HELPER_SOURCES
 #   "${CMAKE_SOURCE_DIR}/test/compare_struct.c"
#)

# 创建库文件（包含src目录的源文件和测试辅助文件）
add_library(regex_lib ${LIB_SOURCES} ${TEST_HELPER_SOURCES})
target_include_directories(regex_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
)

# 主程序
add_executable(main src/main.c test/test.c) # 添加 test/test.c
target_link_libraries(main regex_lib)
target_include_directories(main PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
)

# 测试部分
#enable_testing()

# 收集测试文件（排除compare_struct.c 和 test.c）
#file(GLOB TEST_SOURCES
#    "test/test_task*/*.c"
#    "test/test_task*.c"
#)
#list(REMOVE_ITEM TEST_SOURCES "${CMAKE_SOURCE_DIR}/test/compare_struct.c")
#list(REMOVE_ITEM TEST_SOURCES "${CMAKE_SOURCE_DIR}/test/test.c") # 避免重复使用 test.c

# 为每个测试文件创建测试目标
#foreach(TEST_SOURCE ${TEST_SOURCES})
    # 获取文件名(不含扩展名)作为测试名
#   get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # 创建测试可执行文件
#   add_executable(${TEST_NAME} ${TEST_SOURCE})
#    target_link_libraries(${TEST_NAME} regex_lib)
#    target_include_directories(${TEST_NAME} PUBLIC
#        ${CMAKE_SOURCE_DIR}/include
#       ${CMAKE_SOURCE_DIR}/test
#   )

    # 添加到CTest
#   add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
#endforeach()
