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

set(Additional_Sources
        Standard_Values.h
        )

add_executable(MazeRunner MazeRunner.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources})

set_target_properties("MazeRunner" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")