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

    bool clip(Coordinate *_winMin, Coordinate *_winMax) {
    	Coordinate *coordinate = world_coordinates.front();
        window_coordinates.clear();
    	auto x = coordinate->getX();
    	auto y = coordinate->getY();
    	if (x > (_winMin->getX() + 10) && x < (_winMax->getX() - 10) && y > (_winMin->getY() + 10) && y < (_winMax->getY() - 10)) {
    		window_coordinates.push_back(coordinate);
    		return true;
    	}
		return false;
    }
};

#endif /* end of include guard: POINT_HPP_ */
