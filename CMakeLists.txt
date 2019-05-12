cmake_minimum_required(VERSION 3.12)
project(Progect3_AS_needed)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ..)

add_executable(Progect3_AS_needed main.cpp Lex.h Lex.cpp Scanner.h Scanner.cpp Parser.h
        Parser.cpp Variable.h Variable.cpp Executer.h Executer.cpp Interpretator.h Interpretator.cpp)