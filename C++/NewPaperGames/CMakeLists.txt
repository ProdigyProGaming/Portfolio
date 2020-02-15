cmake_minimum_required(VERSION 3.15)
project(NewPaperGames)

set(CMAKE_CXX_STANDARD 14)

add_executable(NewPaperGames main.cpp RockPaperScissors.cpp RockPaperScissors.h Hangman.cpp Hangman.h Connect4.cpp Connect4.h Battleship.cpp Battleship.h AccountManager.cpp)