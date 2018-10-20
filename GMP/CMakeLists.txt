cmake_minimum_required(VERSION 3.8)
project(GMP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp VigenereCipher.cpp HillCipherImplementation.cpp HillCipherCryptanalysis.cpp)
add_executable(GMP ${SOURCE_FILES})