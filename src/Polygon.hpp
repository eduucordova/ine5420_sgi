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

	bool clip(Coordinate *_winMin, Coordinate *_winMax) {
    	window_coordinates = world_coordinates;
    }
};

#endif /* end of include guard: POLYGON_HPP_ */
