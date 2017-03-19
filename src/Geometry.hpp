#pragma once

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <string>
#include <iostream>
#include <list>

#include "Coordinate.hpp"

struct geometries
{
    enum Type { point, line, polygon };
};
class Geometry {
public:
    string name;
    std::list<Coordinate *> *coordinates;
    geometries::Type type;

    explicit Geometry(geometries::Type _type, string _name, std::list<Coordinate *> *_coordList)
    : type(_type)
    , name(_name)
    , coordinates(_coordList) { }

    virtual ~Geometry() {};
};

#endif /* end of include guard: GEOMETRY_HPP_ */
