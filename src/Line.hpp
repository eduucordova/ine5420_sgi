#pragma once

#ifndef LINE_HPP_
#define LINE_HPP_

#include "Geometry.hpp"
#include <vector>
#include <string>

class Line : public Geometry {
public:
    using Geometry::Geometry;

protected:
    string name;
    std::vector<Coordinate *> *coordinates;
};

#endif /* end of include guard: LINE_HPP_ */
