cmake_minimum_required(VERSION 3.10)
project(Automata-Group-Project_2021-2022)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Maze
        Maze.cpp
        Collectable_DFA.cpp
        miniState.cpp
        )

set(Path
        Path.cpp
        )

set(Player
        Player.cpp
        Enemy.cpp
        )

set(Parser
        Parser.cpp
        )

set(Movement_classes
        MovementChance.cpp 
        MovementState.cpp
        )

set(QT_Utils
        QT_Utils/MazeWindow.cpp
        QT_Utils/MazeBoard.cpp
        QT_Utils/MazeLayout.cpp
        )

set(Additional_Sources
        Standard_Values.h
        )

# Tell cmake where Qt is located
set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(MazeRunner MazeRunner.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources} ${Movement_classes})
add_executable(MazeRunnerVisualisation MazeRunnerVisualisation.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources} ${QT_Utils} ${Movement_classes})

set_target_properties("MazeRunner" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")
set_target_properties("MazeRunnerVisualisation" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")

# Link the library to the executable
target_link_libraries(MazeRunner Qt5::Widgets)
target_link_libraries(MazeRunnerVisualisation Qt5::Core Qt5::Widgets)