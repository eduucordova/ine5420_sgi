#pragma once

#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "Geometry.hpp"
#include <vector>
#include <string>

class Polygon : public Geometry {
public:
    using Geometry::Geometry;

protected:
    string name;
    std::vector<Coordinate *> *coordinates;
};

#endif /* end of include guard: POLYGON_HPP_ */
