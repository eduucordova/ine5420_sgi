#pragma once

#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "Geometry.hpp"

class Polygon : public Geometry {
public:
    using Geometry::Geometry;

    bool clip(Coordinate *_winMin, Coordinate *_winMax) {
        _minPoint->setX(_winMin->getX() + 10);
        _maxPoint->setX(_winMax->getX() - 10);
        _minPoint->setY(_winMin->getY() + 10);
        _maxPoint->setY(_winMax->getY() - 10);

        window_coordinates.clear();

        return PolygonClipping();
    }

private:
    Coordinate * _minPoint = new Coordinate(0, 0);
    Coordinate * _maxPoint = new Coordinate(0, 0);

    bool PolygonClipping() {
        auto previusPoint = world_coordinates.front();

        bool retorno = false;

        for (auto coordinate : world_coordinates)
        {
            auto lineClipped = LiangBarsky(previusPoint, coordinate);
            previusPoint = coordinate;

            retorno = retorno || lineClipped;
        }

        return retorno;
    }

    bool LiangBarsky(Coordinate *p0, Coordinate *p1) {
        float x0 = p0->getX();
        float y0 = p0->getY();
        float x1 = p1->getX();
        float y1 = p1->getY();

        float dx = x1 - x0;
        float dy = y1 - y0;

        float u = 0;
        float v = 1;

        float denom;
        float num;
        float t;

        for (int i = 0; i < 4; ++i)
        {
            if (i == 0) {
                denom = -dx;
                num = -(_minPoint->getX() - x0);
            }
            if (i == 1) {
                denom = dx;
                num = (_maxPoint->getX() - x0);
            }
            if (i == 2) {
                denom = -dy;
                num = -(_minPoint->getY() - y0);
            }
            if (i == 3) {
                denom = dy;
                num = (_maxPoint->getY() - y0);
            }

            t = num / denom;

            // out line
            if (denom == 0 && num < 0)
                return false;

            if (denom < 0) {
                if (t > v)
                    return false;

                if (t > u) 
                    u = t;
            }
            else if (denom > 0) {
                if (t < u)
                    return false;

                if (t < v)
                    v = t;
            }
        }

        window_coordinates.push_back(new Coordinate((x0 + u * dx), (y0 + u * dy)));
        window_coordinates.push_back(new Coordinate((x0 + v * dx), (y0 + v * dy)));

        return true;
    }
};

#endif /* end of include guard: POLYGON_HPP_ */
