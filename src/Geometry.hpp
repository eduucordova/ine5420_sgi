#pragma once

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <string>
#include "Coordinate.hpp"
#include <iostream>
#include <vector>

class Geometry {
protected:
    string name;
    std::vector<Coordinate *> *coordinates;
public:
    explicit Geometry(string _name, std::vector<Coordinate *> *_coordList)
    : name(_name)
    , coordinates(_coordList) { }

    virtual ~Geometry() {};
};

#endif /* end of include guard: GEOMETRY_HPP_ */
