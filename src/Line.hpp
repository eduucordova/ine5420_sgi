#pragma once

#ifndef LINE_HPP_
#define LINE_HPP_

#include <iostream>
#include <list>
#include <string>

#include "Geometry.hpp"

class Line : public Geometry {
public:
    using Geometry::Geometry;

// protected:
//     string name;
//     std::list<Coordinate *> *coordinates;
};

#endif /* end of include guard: LINE_HPP_ */
