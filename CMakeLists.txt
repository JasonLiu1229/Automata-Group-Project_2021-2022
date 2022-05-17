cmake_minimum_required(VERSION 3.10)
project(Automata-Group-Project_2021-2022)

set(CMAKE_CXX_STANDARD 14)
#QT, afblijven!
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

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

# Tell cmake where Qt is located
set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Link the library to the executable
target_link_libraries(MazeRunner Qt5::Core Qt5::Widgets)

add_executable(MazeRunner MazeRunner.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources})

set_target_properties("MazeRunner" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")
