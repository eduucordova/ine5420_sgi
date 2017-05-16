#pragma once

#ifndef COORDINATE_HPP_
#define COORDINATE_HPP_

using namespace std;

#include <iostream>
#include <algorithm> 
#include <vector>
#include <cmath>

class Coordinate {
    private:
    float x;
    float y;

    public:
    Coordinate(float _x, float _y) {
        x = _x;
        y = _y;
    }

    ~Coordinate() {}

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    void setX(float _x) {
        x = _x;
    }

    void setY(float _y) {
        y = _y;
    }

    void updateX(int _x) {
        x += _x;
    }

    void updateY(int _y) {
        y += _y;
    }

    void updateX(float _x) {
        x *= _x;
    }

    void updateY(float _y) {
        y *= _y;
    }

    void transform(const std::vector<std::vector<float>>& _matrix)
    {
        std::vector<float> _vector = { x, y, 1 };
        std::vector<float> newVec = { 0, 0, 0 };

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
};

#endif
