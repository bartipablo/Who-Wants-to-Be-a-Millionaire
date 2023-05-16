cmake_minimum_required(VERSION 3.25)
project(Millionaires)

set(CMAKE_CXX_STANDARD 17)

add_executable(Millionaires main.cpp Question.cpp Question.h Reader.cpp Reader.h Lifelines.cpp Lifelines.h Player.cpp Player.h Writer.cpp Writer.h)
