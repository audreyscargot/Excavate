//
// Created by sushi on 28/09/2026.
//

#include "Pinceau.h"

#include <chrono>
#include <iostream>
#include <random>

static int radius = 7;
static int reach = radius +0.1;

void Pinceau::sphereFunction(std::map<std::vector<int>, double>& _chunk, double _surfaceLevel, bool _isRemoving, int x, int y, int z) {
    /*unsigned a = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(a);

    auto it = _chunk.begin();
    std::advance(it, mt() % _chunk.size());

    int x = it->first[0];
    int y = it->first[1];
    int z = it->first[2];*/

    std::vector<int> _tempPoint = {x, y, z};
    for (int i = -reach; i < reach; i++) {
        for (int j = -reach; j < reach; j++) {
            for (int k = -reach; k < reach; k++) {
                _tempPoint = {x+i, y+j, z+k};
                if (distance(_tempPoint, {x,y,z}) > reach) {
                    continue;
                    }
                if (_chunk.find(_tempPoint) == _chunk.end()) {
                    continue;
                }
                double _hole = _isRemoving ? _surfaceLevel + ((radius - distance(_tempPoint, {x,y,z})) * 0.5) : _surfaceLevel - ((radius - distance(_tempPoint, {x,y,z})) * 0.5) ;
                _chunk[_tempPoint] = _isRemoving ? std::max(_chunk[_tempPoint],_hole) : std::min(_chunk[_tempPoint], _hole);
            }
        }
    }
}

void Pinceau::cubeFunction(std::map<std::vector<int>, double> &_chunk, double _surfaceLevel, bool _isRemoving, int x,
    int y, int z) {

    std::vector<int> _tempPoint = {x, y, z};
    for (int i = -reach; i < reach; i++) {
        for (int j = -reach; j < reach; j++) {
            for (int k = -reach; k < reach; k++) {
                _tempPoint = {x+i, y+j, z+k};
                if (_chunk.find(_tempPoint) == _chunk.end()) {
                    continue;
                }
                double _hole = _isRemoving ? _surfaceLevel + (radius - (radius - x)*(radius-y)*(radius-z) * 0.5) : _surfaceLevel - (radius - (radius - x)*(radius-y)*(radius-z) * 0.5) ;
                _chunk[_tempPoint] = _isRemoving ? std::max(_chunk[_tempPoint],_hole) : std::min(_chunk[_tempPoint], _hole);
            }
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
