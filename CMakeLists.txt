cmake_minimum_required(VERSION 3.5)

project(uni LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(uni src/main.cpp)

add_executable(hw1-sol1 src/homework1/sol1.cpp )#src/as_int.cpp)
add_executable(hw1-sol2 src/homework1/sol2.cpp )#src/as_int.cpp)

add_executable(lab2-sol1 src/lab2/sol1.cpp)
add_executable(lab2-sol2 src/lab2/sol2.cpp)

add_executable(hw2-sol2 src/homework2/sol2.cpp)

include(GNUInstallDirs)
install(TARGETS uni
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
