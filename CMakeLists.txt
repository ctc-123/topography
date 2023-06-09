cmake_minimum_required(VERSION 3.15)
project(topography)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(SDL2_PATH "C:\\dev\\SDL\\SDL2-2.0.18\\i686-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

set(SOURCE_FILES main.cpp)

add_executable(topography main.cpp objects/Map.cpp objects/Map.h objects/Coordinate.cpp objects/Coordinate.h objects/MapSquare.cpp objects/MapSquare.h
        draw/MapDrawer.h draw/MapDrawer.cpp algorithms/Algorithms.cpp algorithms/Algorithms.h controller/InputHandler.cpp controller/InputHandler.h controller/GameController.cpp controller/GameController.h data/DataTypes.h data/ButtonMap.h objects/Unit.cpp objects/Unit.h controller/UnitManager.cpp controller/UnitManager.h objects/Vector.cpp objects/Vector.h data/TraversalVectors.cpp data/TraversalVectors.h data/PriorityQueue.h controller/MapIOHandler.cpp controller/MapIOHandler.h controller/MapEditor.cpp controller/MapEditor.h)


target_link_libraries(topography ${SDL2_LIBRARY} )

