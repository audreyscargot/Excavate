#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "TerrainCore/MarchingCubes.h"
#include "TerrainCore/PerlinNoise.h"
#include "TerrainCore/Terrain.h"
#include "TerrainCore/Pinceau.h"

class Terrain;

static int landscapeSize = 2;

bool exportOBJ(std::ofstream& out, const std::vector<std::vector<std::vector<double>>>& vertices, const std::vector<std::vector<std::vector<double>>>& normals, size_t& offset) {
    for (const auto& tri : vertices) { //crée les vertex
        for (int v = 0; v < 3; ++v)
            out << "v " << tri[v][0] << " " << tri[v][1] << " " << tri[v][2] << "\n";
    }

    for (const auto& norm : normals) {
        for (int v = 0; v < 3; ++v)
            out << "vn " << norm[v][0] << " " << norm[v][1] << " " << norm[v][2] << "\n";
    }

    for (size_t t = 0; t < vertices.size(); ++t) {
        size_t i = offset + t * 3 + 1;
        out << "f " << i << "//" << i << " " << i + 1 << "//" << i+1 << " " << " " << i + 2 << "//" << i+2 << " " "\n"; //crée les faces
        //out << "f " << i << " " << i + 1 << " " <<  i + 2 << "\n"; // sans smooth
    }


        offset += vertices.size() * 3;

    return true;
}

int main() {

    //pour perlin
    unsigned a = std::chrono::system_clock::now().time_since_epoch().count();
    PerlinNoise::makePermutationTable(a);

    std::vector<std::map<std::vector<int>, double>> Landscape;
    int size = TerrainCore::Terrain::GetChunkSize();

    //on génère les chunks
    for (int i = 0; i < landscapeSize; ++i) {
        for (int j = 0; j < landscapeSize; ++j) {
            for (int k = 0; k < landscapeSize; ++k) {
                auto chunk = TerrainCore::Terrain::generateTerrain(i,j,k);
                Landscape.push_back(std::move(chunk));
            }
        }
    }

    //on creuse
    int coord = size * landscapeSize / 2;
    Pinceau::sphereBrush(Landscape, MarchingCubes::GetSurfaceLevel(), true, coord, coord, coord, TerrainCore::Terrain::GetChunkSize(), landscapeSize);


    //pour fichier obj
    std::ofstream out("C:/Users/sushi/Documents/Temp/terrain.obj");
    size_t offset = 0;

    for (int i = 0; i < landscapeSize; ++i) {
        for (int j = 0; j < landscapeSize; ++j) {
            for (int k = 0; k < landscapeSize; ++k) {
                int index = i * landscapeSize * landscapeSize + j * landscapeSize + k;

                //marching cubes
                for (int a = 0; a < size; a++) {
                    for (int b = 0; b < size; b++) {
                        for (int c = 0; c < size ; c++) {
                            MarchingCubes::sampleVertices(Landscape[index], a,b,c,i,j,k, size);
                        }
                    }
                }
                std::cout << k << std::endl;
                exportOBJ(out, MarchingCubes::GetTriangles(), MarchingCubes::GetNormals(), offset);
                MarchingCubes::Reset();
            }
        }
    }

    std::cout << landscapeSize << std::endl;
}