#ifndef CLION_TERRAIN_H
#define CLION_TERRAIN_H
#include <map>
#include <vector>

namespace TerrainCore {

class Terrain {

public:

    static int chunkSize;

    static std::map<std::vector<int>, double> createChunk(int _chunkSize);

    static std::map<std::vector<int>, double> generateChunkNoise(std::map<std::vector<int>, double> _chunk);

    static std::map<std::vector<int>, double> generateTerrain();

    static int GetChunkSize();

};

}




#endif //CLION_TERRAIN_H
