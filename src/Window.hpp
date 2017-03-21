#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Coordinate.hpp"

class Window {
public:
    Window(const Coordinate &_Wmin, const Coordinate &_Wmax)
    : Wmin(_Wmin)
    , Wmax(_Wmax)
    {
        populateForDebug();
    }

    ~Window() { }

    void populateForDebug() {
        std::list<Coordinate*> coordinates;
        coordinates.push_back(new Coordinate(25, 25));
        coordinates.push_back(new Coordinate(32, 76));
        coordinates.push_back(new Coordinate(87, 69));
        coordinates.push_back(new Coordinate(92, 32));
        coordinates.push_back(new Coordinate(41, 46));
        AddPolygon(coordinates);
    }

    void moveUp(int steps)
    {
        Wmax.updateY(steps);
        Wmin.updateY(steps);
    }

    void moveDown(int steps)
    {
        Wmax.updateY(-1 * steps);
        Wmin.updateY(-1 * steps);
    }

    void moveLeft(int steps)
    {
        Wmax.updateX(-1 * steps);
        Wmin.updateX(-1 * steps);
    }

    void moveRight(int steps)
    {
        Wmax.updateX(steps);
        Wmin.updateX(steps);
    }

    void zoom(int size)
    {
        Wmax.updateX(size);
        Wmax.updateY(size);
        Wmin.updateX(-1 * size);
        Wmin.updateY(-1 * size);
    }

    void AddPoint(std::list<Coordinate*> coordinates) {
        Geometry *point = new Point(geometries::point, "point_" + std::to_string(pointCount++), coordinates);
        displayFile.push_back(point);
    }

    void AddLine(std::list<Coordinate*> coordinates) {
        Geometry *line = new Line(geometries::line, "line_" + std::to_string(lineCount++), coordinates);
        displayFile.push_back(line);
    }

    void AddPolygon(std::list<Coordinate*> coordinates) {
        Geometry *polygon = new Polygon(geometries::polygon, "polygon_" + std::to_string(polygonCount++), coordinates);
        displayFile.push_back(polygon);
    }

    Coordinate *getMinPoint()
    {
      return &Wmin;
    }

    Coordinate *getMaxPoint()
    {
      return &Wmax;
    }

    std::list<Geometry *> displayFile;
private:
    int pointCount = 0;
    int lineCount = 0;
    int polygonCount = 0;
    Coordinate Wmin, Wmax;
};

#endif /* end of include guard: WINDOW_HPP_ */
