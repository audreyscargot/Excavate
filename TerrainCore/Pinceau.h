#ifndef CLION_PINCEAU_H
#define CLION_PINCEAU_H
#include <map>
#include <vector>


class Pinceau {

    public:

    static void sphereTestFunction(std::map<std::vector<int>, double>& _chunk, double _surfaceLevel, bool _isRemoving);

    static double distance(std::vector<int> _vec1, std::vector<int> _vec2);

};


#endif //CLION_PINCEAU_H
