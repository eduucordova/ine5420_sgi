#pragma once

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <string>
#include <iostream>
#include <list>

#include "Coordinate.hpp"
#include "Transformation.hpp"

struct geometries
{
    enum Type { point, line, polygon };
};
class Geometry {
public:
    string name;
    std::list<Coordinate *> coordinates;
    geometries::Type type;

    explicit Geometry(geometries::Type _type, string _name, std::list<Coordinate *> _coordList)
    : type(_type)
    , name(_name)
    , coordinates(_coordList) { }

    virtual ~Geometry() {};

    const Coordinate GetObjectCenter() {
        double xSum = 0.0;
        double ySum = 0.0;

        for(auto coordinate : coordinates) {
            xSum += coordinate->getX();
            ySum += coordinate->getY();
        }

        auto Cx = xSum / coordinates.size();
        auto Cy = ySum / coordinates.size();

        return Coordinate(Cx, Cy);
    }

    void translate(float dx, float dy) {
        auto T_matrix = Transformation::TranslateMatrix(dx, dy);

        for(auto coordinate : coordinates) {
            coordinate->transform(T_matrix);
        }
    }

    void scaling(float Sx, float Sy) {
        Coordinate center = GetObjectCenter();

        auto T_matrix1 = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);
        auto S_matrix = Transformation::ScalingMatrix(Sx, Sy);
        auto T_matrix2 = Transformation::TranslateMatrix(center.getX(), center.getY());

        auto result = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, S_matrix), T_matrix2);

        for(auto coordinate : coordinates) {
            coordinate->transform(result);
        }
    }

    void rotate(float angle) {
        Coordinate center = GetObjectCenter();

        auto T_matrix1 = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);
        auto R_matrix = Transformation::RotateMatrix(angle);
        auto T_matrix2 = Transformation::TranslateMatrix(center.getX(), center.getY());

        auto result = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, R_matrix), T_matrix2);

        for(auto coordinate : coordinates) {
            coordinate->transform(result);
        }
    }
};

#endif /* end of include guard: GEOMETRY_HPP_ */
