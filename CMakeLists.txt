cmake_minimum_required(VERSION 3.20)
project(Automata-Group-Project_2021-2022)

set(CMAKE_CXX_STANDARD 14)

set(Maze
        Maze.h
        Maze.cpp
        )

set(Path
        Path.h
        Path.cpp
        Coin.h
        Coin.cpp)

set(Player
        Player.h
        Player.cpp
        Enemy.h
        Enemy.cpp)

add_executable(MazeRunner main.cpp)