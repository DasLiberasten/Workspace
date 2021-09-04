cmake_minimum_required(VERSION 3.17)
project(My_Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(My_Client Client.cpp Sock_client.h Sock_client.cpp)