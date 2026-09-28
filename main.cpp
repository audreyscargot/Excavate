#include <iostream>
#include "TerrainCore/PerlinNoise.h"
#include "TerrainCore/Terrain.h"
#include "TerrainCore/Pinceau.h"

int main() {

    PerlinNoise::makePermutationTable();
    std::map<std::vector<int>, double> Chunk = TerrainCore::Terrain::generateTerrain();
    Pinceau::sphereTestFunction(Chunk);
}