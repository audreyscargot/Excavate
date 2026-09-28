//
// Created by sushi on 28/09/2026.
//

#include "Pinceau.h"

#include <chrono>
#include <iostream>
#include <random>

static int radius = 2;

void Pinceau::sphereTestFunction(std::map<std::vector<int>, double>& _chunk) {

    unsigned a = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(a);

    auto it = _chunk.begin();
    std::advance(it, mt() % _chunk.size());
    const std::vector<int> _randomKey = it->first;

    int x = _randomKey[0];
    int y = _randomKey[1];
    int z = _randomKey[2];

    std::vector<std::vector<int>> _sphere;
    std::vector<int> _tempPoint = {x, y, z};
    for (int i = -radius; i < radius+1; i++) {
        for (int j = -radius; j < radius+1; j++) {
            for (int k = -radius; k < radius+1; k++) {
                _tempPoint = {x+i, y+j, z+k};
                if (distance(_tempPoint, {x,y,z}) <= radius) {
                    _sphere.push_back(_tempPoint);
                }
            }
        }
    }

    for (int i = 0; i < _sphere.size(); i++) {
        if (_chunk.find(_sphere[i]) != _chunk.end()) {
            _chunk[_sphere[i]] = 0;
        }
    }

}

double Pinceau::distance(std::vector<int> _vec1, std::vector<int> _vec2) {

    double dist = 0;
    int distX = _vec1[0] - _vec2[0];
    int distY = _vec1[1] - _vec2[1];
    int distZ = _vec1[2] - _vec2[2];
    dist = sqrt((distX*distX)+(distY*distY)+(distZ*distZ));

    return dist;
}
