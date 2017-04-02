#pragma once

#ifndef COORDINATE_HPP_
#define COORDINATE_HPP_

using namespace std;

#include <iostream>
#include <algorithm> 
#include <vector>
#include <cmath>

#define PI 3.14159265;

class Coordinate {
    private:
    double x;
    double y;

    public:
    Coordinate(double _x, double _y) {
        x = _x;
        y = _y;
    }

    ~Coordinate() {}

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    void setX(double _x) {
        x = _x;
    }

    void setY(double _y) {
        y = _y;
    }

    void updateX(int _x) {
        x += _x;
    }

    void updateY(int _y) {
        y += _y;
    }

    void updateX(double _x) {
        x *= _x;
    }

    void updateY(double _y) {
        y *= _y;
    }

    void transform(const std::vector<std::vector<float>>& _matrix)
    {
        std::vector<double> _vector = { x, y, 1 };
        std::vector<double> newVec = { 0, 0, 0 };

        for (std::size_t i = 0; i < _matrix.size(); ++i)
        {
            for (std::size_t j = 0; j < _matrix[i].size(); ++j)
            {
                newVec[j] += _vector[i] * _matrix[i][j];
            }
        }

        setX(newVec[0]);
        setY(newVec[1]);
    }

    float angleBetweenY() {
        float v = sqrt(pow(x, 2) + pow(y, 2)); // sqrt(x² + y²)
        float u = sqrt(pow(0, 2) + pow(1, 2)); // Y axis

        // cout << "[-1,1]" << (x*0 + y*1) / (v*u) << endl;

        return (acos(max(min(((x*0 + y*1) / (v*u)), 1.0),-1.0)) * 180.0) / 3.14159265;
    }

    double angle() 
    {
        double dot = x*0 + y*1;      // dot product
        double det = x*1 - y*0;      // determinant
        double angle = atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)

        return angle * 180.0 / PI;
    }
};

#endif
