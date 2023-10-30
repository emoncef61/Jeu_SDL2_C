cmake_minimum_required(VERSION 3.24)
project(Jeu_zz11 C)

set(CMAKE_C_STANDARD 11)

add_executable(Jeu_zz11 main.c mapGenerator.c mapGenerator.h Simulation.c )
target_link_libraries(Jeu_zz11 PRIVATE /opt/homebrew/lib/libSDL2.a)
target_link_libraries(Jeu_zz11 PRIVATE /opt/homebrew/lib/libSDL2_image.a)
target_link_libraries(Jeu_zz11 PRIVATE /opt/homebrew/lib/libSDL2_ttf.a)
target_include_directories(Jeu_zz11 PRIVATE /opt/homebrew/include)
