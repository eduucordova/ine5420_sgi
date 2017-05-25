#pragma once

#ifndef COORDINATE3D_HPP_
#define COORDINATE3D_HPP_

using namespace std;

#include <iostream>
#include <algorithm> 
#include <vector>
#include <cmath>

class Coordinate3D {
    private:
    float x;
    float y;
    float z;

    public:
    Coordinate3D(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    ~Coordinate3D() {}

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    float getZ() {
        return z;
    }

    void setX(float _x) {
        x = _x;
    }

    void setY(float _y) {
        y = _y;
    }

    void setZ(float _z) {
        z = _z;
    }

    void updateX(int _x) {
        x += _x;
    }

    void updateY(int _y) {
        y += _y;
    }

    void updateZ(int _z) {
        z += _z;
    }

    void updateX(float _x) {
        x *= _x;
    }

    void updateY(float _y) {
        y *= _y;
    }

    void updateZ(float _z) {
        z *= _z;
    }

    void transform(const std::vector<std::vector<float>>& _matrix)
    {
        std::vector<float> _vector = { x, y, z, 1 };
        std::vector<float> newVec = { 0, 0, 0, 0 };

        for (std::size_t i = 0; i < _matrix.size(); ++i)
        {
            for (std::size_t j = 0; j < _matrix[i].size(); ++j)
            {
                newVec[j] += _vector[i] * _matrix[i][j];
            }
        }

        setX(newVec[0]);
        setY(newVec[1]);
        setZ(newVec[2]);
    }
};

#endif
