cmake_minimum_required(VERSION 3.17)
project(My_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(My_Server Server.cpp Sock_serv.cpp Sock_serv.h Database.cpp Database.h Poliz.cpp Poliz.h Analyzer.cpp Analyzer.h Executor.cpp Executor.h)