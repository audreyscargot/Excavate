#include "Terrain.h"

#include <iostream>
#include <ostream>

#include "PerlinNoise.h"

int TerrainCore::Terrain::chunkSize = 32;

std::map<std::vector<int>, double> TerrainCore::Terrain::createChunk(int _chunkSize) {

    std::map<std::vector<int>, double> _chunkPoints;
    for (int x = 0; x < _chunkSize+1; x++) {
        for (int y = 0; y < _chunkSize+1; y++) {
            for (int z = 0; z < _chunkSize+1; z++) {
                _chunkPoints.insert(std::pair<std::vector<int>, double>({x, y, z}, 0));
            }
        }
    }
    return _chunkPoints;
}

std::map<std::vector<int>, double> TerrainCore::Terrain::generateChunkNoise(std::map<std::vector<int>, double> _chunk) {

    int index = 0;
    for (auto& _point : _chunk) {
        std::vector<int> _pointCoordinate = _point.first;
        _point.second = PerlinNoise::makeNoise(_pointCoordinate[0]+0.5, _pointCoordinate[1]+0.5, _pointCoordinate[2]+0.5);
        index++;
    }
    return _chunk;
}

std::map<std::vector<int>, double> TerrainCore::Terrain::generateTerrain() {

    std::map<std::vector<int>, double> _chunk = createChunk(chunkSize);
    _chunk = generateChunkNoise(_chunk);
    return _chunk;
}
