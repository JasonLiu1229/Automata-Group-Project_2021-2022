cmake_minimum_required(VERSION 3.10)
project(Automata-Group-Project_2021-2022)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

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

set(QT_Utils)

set(QT_UI
        QT_UI_Design/ui_MazeWindow.cpp
        )

set(Additional_Sources
        Standard_Values.h
        )

# Tell cmake where Qt is located
set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(MazeRunner MazeRunner.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources} ${Movement_classes})
add_executable(MazeRunnerNoColor MazeRunnerVisNew.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources} ${Movement_classes} ${QT_UI})
add_executable(MazeRunnerVisNew MazeRunnerVisNew.cpp ${Parser} ${Maze} ${Player} ${Path} ${Additional_Sources} ${Movement_classes} ${QT_UI} ${QT_Utils})

set_target_properties("MazeRunner" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")
set_target_properties("MazeRunnerNoColor" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")
set_target_properties("MazeRunnerVisNew" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Levels/JSON-Files")

# Link the library to the executable
target_link_libraries(MazeRunner Qt5::Widgets)
target_link_libraries(MazeRunnerNoColor Qt5::Core Qt5::Widgets)
target_link_libraries(MazeRunnerVisNew Qt5::Core Qt5::Widgets)

set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '${PROJECT_SOURCE_DIR}/MinoScape.lnk' '{PROJECT_SOURCE_DIR}/Levels/JSON-Files/MazeRunnerVisNew.exe' '-foo -bar'"
        )