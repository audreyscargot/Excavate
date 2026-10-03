cmake_minimum_required(VERSION 4.3)
project(Excavate)

set(CMAKE_CXX_STANDARD 17)

add_executable(Excavate main.cpp
        TerrainCore/Terrain.cpp
        TerrainCore/Terrain.h
        TerrainCore/PerlinNoise.cpp
        TerrainCore/PerlinNoise.h
        TerrainCore/Pinceau.cpp
        TerrainCore/Pinceau.h
        TerrainCore/MarchingCubes.cpp
        TerrainCore/MarchingCubes.h)
