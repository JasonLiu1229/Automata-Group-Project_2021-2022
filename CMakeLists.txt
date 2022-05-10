cmake_minimum_required(VERSION 3.20)
project(Automata-Group-Project_2021-2022)

set(CMAKE_CXX_STANDARD 14)

set(Maze
        Maze.h
        Maze.cpp
        Collectable_DFA.h
        Collectable_DFA.cpp
        )

set(Path
        Path.h
        Path.cpp
        Key.h
        Key.cpp
        )

set(Player
        Player.h
        Player.cpp
        Enemy.h
        Enemy.cpp
        )

set(Parser
        Parser.h
        Parser.cpp
        )

add_executable(MazeRunner MazeRunner.cpp ${Parser} ${Maze} ${Player} ${Path})