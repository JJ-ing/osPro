cmake_minimum_required(VERSION 3.15)
project(CopyByProcesses)

set(CMAKE_CXX_STANDARD 14)

add_executable(CopyByProcesses main.cpp head.h fromSourceToBufA.cpp fromBufAToBufB.cpp fromBufBToDestination.cpp fromSourceToBufA.cpp)