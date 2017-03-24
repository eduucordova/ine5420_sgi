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

    string AddPoint(std::list<Coordinate*> coordinates) {
        string name = "point_" + std::to_string(pointCount++);
        Geometry *point = new Point(geometries::point, name, coordinates);
        displayFile.push_back(point);

        return name;
    }

    string AddLine(std::list<Coordinate*> coordinates) {
        string name = "line_" + std::to_string(lineCount++);
        Geometry *line = new Line(geometries::line, name, coordinates);
        displayFile.push_back(line);

        return name;
    }

    string AddPolygon(std::list<Coordinate*> coordinates) {
        string name = "polygon_" + std::to_string(polygonCount++);
        Geometry *polygon = new Polygon(geometries::polygon, name, coordinates);
        displayFile.push_back(polygon);

        return name;
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
    int pointCount = 1;
    int lineCount = 1;
    int polygonCount = 1;
    Coordinate Wmin, Wmax;
};

#endif /* end of include guard: WINDOW_HPP_ */
