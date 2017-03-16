#pragma once

#ifndef POINT_HPP_
#define POINT_HPP_

#include "Geometry.hpp"
#include <vector>
#include <string>

class Point : public Geometry {
public:
    using Geometry::Geometry;

protected:
    string name;
    std::vector<Coordinate *> *coordinates;
};

#endif /* end of include guard: POINT_HPP_ */
