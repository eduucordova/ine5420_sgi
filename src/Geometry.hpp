#pragma once

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <string>
#include <iostream>
#include <list>

#include "Coordinate3D.hpp"
#include "Coordinate.hpp"
#include "Transformation.hpp"

struct geometries
{
    enum Type { point, line, polygon, curve };
};
class Geometry {
public:
    string name;
    std::list<Coordinate3D *> world_coordinates;
    std::list<Coordinate *> window_coordinates;
    geometries::Type type;

    explicit Geometry(geometries::Type _type, string _name, std::list<Coordinate3D *> _coordList)
    : type(_type)
    , name(_name)
    , world_coordinates(_coordList)
    { }

    virtual ~Geometry() {};

    const Coordinate3D GetObjectCenter() {
        float xSum = 0.0;
        float ySum = 0.0;
        float zSum = 0.0;

        for(auto coordinate : world_coordinates) {
            xSum += coordinate->getX();
            ySum += coordinate->getY();
            zSum += coordinate->getZ();
        }

        auto Cx = xSum / world_coordinates.size();
        auto Cy = ySum / world_coordinates.size();
        auto Cz = zSum / world_coordinates.size();

        return Coordinate3D(Cx, Cy, Cz);
    }

    void translate(float dx, float dy, float dz) {
        auto T_matrix = Transformation::TranslateMatrix3D(dx, dy, dz);

        for(auto coordinate : world_coordinates) {
            coordinate->transform(T_matrix);
        }
    }

    void scaling(float Sx, float Sy, float Sz) {
        Coordinate3D center = GetObjectCenter();

        auto T_matrix1 = Transformation::TranslateMatrix3D(center.getX() * -1, center.getY() * -1, center.getZ() * -1);
        auto S_matrix = Transformation::ScalingMatrix3D(Sx, Sy, Sz);
        auto T_matrix2 = Transformation::TranslateMatrix3D(center.getX(), center.getY(), center.getZ());

        auto result = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, S_matrix), T_matrix2);

        for(auto coordinate : world_coordinates) {
            coordinate->transform(result);
        }
    }

    void rotate(float angle) {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float d = 0.0f;
        float cosX = 0.0f;
        float sinX = 0.0f;
        float cosZ = 0.0f;
        float sinZ = 0.0f;

        for(auto coordinate : world_coordinates) {
            x = coordinate->getX();
            y = coordinate->getY();
            z = coordinate->getZ();

            d = sqrt(pow(y, 2) + pow(z, 2));
            cosX = acos(z/d);
            sinX = acos(y/d);
            cosZ = acos(d);
            sinZ = acos(x);


            auto T1 = Transformation::TranslateMatrix3D(x * -1, y * -1, z * -1);
            auto Rx1 = Transformation::RotateMatrix3Dx(cosX, sinX);
            auto Rz1 = Transformation::RotateMatrix3Dy(cosZ, sinZ);
            auto Ry = Transformation::RotateMatrix3Dz(angle);
            auto Rz2 = Transformation::RotateMatrix3Dy(-1 * cosZ, -1 * sinZ);
            auto Rx2 = Transformation::RotateMatrix3Dx(-1 * cosX, -1 * sinX);
            auto T2 = Transformation::TranslateMatrix3D(x, y, z);

            auto result = Transformation::matrixProduct(
                Transformation::matrixProduct(
                    Transformation::matrixProduct(
                        Transformation::matrixProduct(
                            Transformation::matrixProduct(
                                Transformation::matrixProduct(T1, Rx1), Rz1), Ry), Rz2), Rx2), T2);

            coordinate->transform(result);
        }
    }
};

#endif /* end of include guard: GEOMETRY_HPP_ */
