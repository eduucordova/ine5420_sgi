#pragma once

#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <list>
#include <string>

#include "Geometry.hpp"

class Point : public Geometry {
public:
    using Geometry::Geometry;

protected:
    string name;
    std::list<Coordinate *> *coordinates;
};

#endif /* end of include guard: POINT_HPP_ */
