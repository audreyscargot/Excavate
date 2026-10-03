//
// Created by sushi on 28/09/2026.
//

#ifndef EXCAVATE_MARCHINGCUBES_H
#define EXCAVATE_MARCHINGCUBES_H
#include <map>
#include <vector>


class MarchingCubes {

public:

    static void sampleVertices(const std::map<std::vector<int>, double>& _chunk, int x, int y, int z);

    static double makeValue(const std::map<std::vector<int>, double>& _chunk, int x, int y, int z, double _deadValue);

    static std::vector<double> makeGradient(const std::map<std::vector<int>, double>& _chunk, int x, int y, int z);

    static std::vector<double> makeNormals(const std::map<std::vector<int>, double>& _chunk, int xa, int ya, int za, int xb, int yb, int zb, double P);

    static std::vector<double> interpolate(std::vector<int> p1, std::vector<int> p2, double value1, double value2);

    static int createTriangles(int _cubeIndex, const std::vector<std::vector<double>>& _vertList, const std::vector<std::vector<double>>& _normalList);

    static std::vector<std::vector<std::vector<double>>> GetTriangles();

    static std::vector<std::vector<std::vector<double>>> GetNormals();


};


#endif //EXCAVATE_MARCHINGCUBES_H
