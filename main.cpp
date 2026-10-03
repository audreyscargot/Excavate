#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "TerrainCore/MarchingCubes.h"
#include "TerrainCore/PerlinNoise.h"
#include "TerrainCore/Terrain.h"
#include "TerrainCore/Pinceau.h"

class Terrain;

bool exportOBJ(const std::string& path, std::vector<std::vector<std::vector<double>>> vertices, std::vector<std::vector<std::vector<double>>> normals) {
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Error opening output file" << std::endl;
        return false;
    }

    size_t index = 1;
    for (const auto& tri : vertices) { //crée les vertex
        for (int v = 0; v < 3; ++v)
            out << "v " << tri[v][0] << " " << tri[v][1] << " " << tri[v][2] << "\n";
        index += 3;
    }

    index = 1;
    for (const auto& norm : normals) {
        for (int v = 0; v < 3; ++v)
            out << "vn " << norm[v][0] << " " << norm[v][1] << " " << norm[v][2] << "\n";

        out << "f " << index << "//" << index << " " << index + 1 << "//" << index+1 << " " << " " << index + 2 << "//" << index+2 << " " "\n"; //crée les faces
        //out << "f " << index << " " << index + 1 << " " <<  index + 2 << "\n"; // sans smooth

        index += 3;
    }

    return true;
}

int main() {

    PerlinNoise::makePermutationTable();
    std::map<std::vector<int>, double> Chunk = TerrainCore::Terrain::generateTerrain();
    int size = TerrainCore::Terrain::GetChunkSize();
    Pinceau::sphereFunction(Chunk, -0.2, true, floor(size/2), floor(size/2), floor(size/2));
    std::cout << "floor " << floor(Chunk.size()/2) << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << std::endl;
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size ; k++) {
                MarchingCubes::sampleVertices(Chunk, i, j, k);
            }
        }
    }
    exportOBJ("C:/Users/sushi/Documents/Temp/terrain.obj", MarchingCubes::GetTriangles(), MarchingCubes::GetNormals());
}