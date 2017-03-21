#pragma once

#ifndef COORDINATE_HPP_
#define COORDINATE_HPP_

using namespace std;

#include <iostream>
#include <vector>

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

    void updateX(double _x) {
        x += _x;
    }

    void updateY(double _y) {
        y += _y;
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
};

#endif
