# 规定最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 声明项目名称
project(FDTD_1D_Solver)

# 指定使用 C++11 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 告诉编译器去哪里找头文件 (也就是刚才的 include 文件夹)
include_directories(include)

# 核心命令：将 src/main.cpp 编译成名为 fdtd_solver 的可执行文件
add_executable(fdtd_solver src/main.cpp)
