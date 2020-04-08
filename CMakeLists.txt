cmake_minimum_required(VERSION 3.13)
project(OxymetreDePouls C)

set(CMAKE_C_STANDARD 99)

add_executable(OxymetreDePouls main.c fichiers.c fir.c iir.c lecture.c integration.c affichage.c mesure.c)