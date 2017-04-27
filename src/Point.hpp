#pragma once

#ifndef POINT_HPP_
#define POINT_HPP_

#include "Geometry.hpp"

class Point : public Geometry {
public:
    using Geometry::Geometry;

    bool clip(Coordinate *_winMin, Coordinate *_winMax) {
    	Coordinate *coordinate = world_coordinates.front();
        window_coordinates.clear();

        _minPoint->setX(_winMin->getX() + 10);
        _maxPoint->setX(_winMax->getX() - 10);
        _minPoint->setY(_winMin->getY() + 10);
        _maxPoint->setY(_winMax->getY() - 10);

    	auto x = coordinate->getX();
    	auto y = coordinate->getY();

    	if (x > _minPoint->getX() && x < _maxPoint->getX() && y > _minPoint->getY() && y < _maxPoint->getY()) {
    		window_coordinates.push_back(coordinate);
    		return true;
    	}
		return false;
    }
    
private:
    Coordinate * _minPoint = new Coordinate(0, 0);
    Coordinate * _maxPoint = new Coordinate(0, 0);
};

#endif /* end of include guard: POINT_HPP_ */
