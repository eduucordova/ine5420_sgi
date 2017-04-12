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
    
    bool clip(Coordinate *_winMin, Coordinate *_winMax) {
    	_minPoint->setX(_winMin->getX() + 10);
    	_maxPoint->setX(_winMax->getX() - 10);
    	_minPoint->setY(_winMin->getY() + 10);
    	_maxPoint->setY(_winMax->getY() - 10);
    	auto p0 = world_coordinates.front();
    	auto p1 = world_coordinates.back();

		window_coordinates.clear();

    	return CohenSutherland(p0, p1);
    }

private:
	Coordinate * _minPoint = new Coordinate(0, 0);
	Coordinate * _maxPoint = new Coordinate(0, 0);
	const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

	bool CohenSutherland(Coordinate *p0, Coordinate *p1) {
		float x0 = p0->getX();
		float y0 = p0->getY();
		float x1 = p1->getX();
		float y1 = p1->getY();

		int regionCode0 = computeregionCode(x0, y0);
		int regionCode1 = computeregionCode(x1, y1);

		cout << "regionCode0:" << regionCode0 << endl;
		cout << "regionCode1:" << regionCode1 << endl;
		while (true) {
			if (!(regionCode0 | regionCode1))
			{
				window_coordinates.push_back(new Coordinate(x0, y0));
				window_coordinates.push_back(new Coordinate(x1, y1));
				return true;
			}
			else if (regionCode0 & regionCode1)
				return false;
			else
			{
				float x = 0;
				float y = 0;

				int regionCodeOut = regionCode0 ? regionCode0 : regionCode1;

				if (regionCodeOut & TOP)
				{
					float yTop = _maxPoint->getY();
					x = ((x1 - x0) / (y1 - y0)) * (yTop - y0) + x0;
					y = yTop;
				}
				else if (regionCodeOut & BOTTOM)
				{
					float yBottom = _minPoint->getY();
					x = ((x1 - x0) / (y1 - y0)) * (yBottom - y0) + x0;
					y = yBottom;
				}
				else if (regionCodeOut & RIGHT)
				{
					float xRight = _maxPoint->getX();
					y = ((y1 - y0) / (x1 - x0)) * (xRight - x0) + y0;
					x = xRight;
				}
				else if (regionCodeOut & LEFT)
				{
					float xLeft = _minPoint->getX();
					y = ((y1 - y0) / (x1 - x0)) * (xLeft - x0) + y0;
					x = xLeft;
				}

				if (regionCodeOut == regionCode0)
				{
					x0 = x;
					y0 = y;
					regionCode0 = computeregionCode(x0, y0);
				}
				else
				{
					x1 = x;
					y1 = y;
					regionCode1 = computeregionCode(x1, y1);
				}
			}
		}
		return true;
	}


	int computeregionCode(float x, float y)
	{
		int code = INSIDE;

		if (x < _minPoint->getX())           // to the left of clip window
			code |= LEFT;
		else if (x > _maxPoint->getX())      // to the right of clip window
			code |= RIGHT;
		if (y < _minPoint->getY())           // below the clip window
			code |= BOTTOM;
		else if (y > _maxPoint->getY())      // above the clip window
			code |= TOP;

		return code;
	}
};

#endif /* end of include guard: LINE_HPP_ */
