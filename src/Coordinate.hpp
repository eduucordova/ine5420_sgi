#pragma once

#ifndef COORDINATE_HPP_
#define COORDINATE_HPP_

using namespace std;

class Coordinate {
private:
	double x;
	double y;

public:
	Coordinate(double _x, double _y) {
		x = _x;
		y = _y;
	}

	~Coordinate() {}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	void setX(double _x) {
		x = _x;
	}

	void setY(double _y) {
		y = _y;
	}

};

#endif
