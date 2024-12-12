cmake_minimum_required(VERSION 3.10)
project(RegexProject)

# 设置C标准
set(CMAKE_C_STANDARD 11)

# 收集源文件(除了src/main.c和src/read_file目录下的文件)
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/main.c")
file(GLOB_RECURSE READ_FILE_SOURCES "${CMAKE_SOURCE_DIR}/src/read_file/*.c")
list(REMOVE_ITEM LIB_SOURCES ${READ_FILE_SOURCES})

# 创建库文件（包含src目录的源文件和测试辅助文件）
add_library(regex_lib ${LIB_SOURCES})

target_include_directories(regex_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/test
)

# 主程序
add_executable(main src/main.c test/test.c)

# 添加 test/test.c
target_link_libraries(main regex_lib)
target_include_directories(main PUBLIC 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/test
)
