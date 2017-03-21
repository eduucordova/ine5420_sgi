#pragma once

#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include <list>
#include <iostream>
#include <string>

#include "Geometry.hpp"

class Polygon : public Geometry {
public:
    using Geometry::Geometry;

// protected:
//     string name;
//     std::list<Coordinate *> *coordinates;
};

#endif /* end of include guard: POLYGON_HPP_ */
