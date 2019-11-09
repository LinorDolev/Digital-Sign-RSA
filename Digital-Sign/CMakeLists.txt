cmake_minimum_required(VERSION 3.14)
project(Digital_Sign)

set(CMAKE_CXX_STANDARD 14)

add_executable(Digital_Sign main.cpp errors.h errors.cpp files.h files.cpp hash.h hash.cpp rsa.h rsa.cpp)