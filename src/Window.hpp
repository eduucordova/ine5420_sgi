#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cmath>

#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Coordinate.hpp"

class Window {
public:
    Window(const Coordinate &_world_min, const Coordinate &_world_max)
    : world_min(_world_min)
    , world_max(_world_max)
    {
    }

    ~Window() { }

    void moveUp(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix(0, steps);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveDown(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix(0, steps * -1);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveLeft(int steps)
    {

        auto T_matrix = Transformation::TranslateMatrix(steps * -1, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveRight(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix(steps, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void zoom(double Sx, double Sy)
    {
        Coordinate center = GetWindowCenter();

        auto T_matrix1 = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);
        auto S_matrix = Transformation::ScalingMatrix(Sx, Sy);
        auto T_matrix2 = Transformation::TranslateMatrix(center.getX(), center.getY());

        auto R_matrix = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, S_matrix), T_matrix2);

        world_max.transform(R_matrix);
        world_min.transform(R_matrix);
    }

    void rotate(double _angle) {
        Coordinate center = GetWindowCenter();

        for (auto geometry : displayFile) {
            geometry->rotate(&center, _angle * -1);
        }
    }

    void clip() {
        clippedDisplayFile.clear();
        for (auto geometry : displayFile) {
            switch (geometry->type) {
                case geometries::point:
                {
                    Point *point = dynamic_cast<Point*>(geometry);
                    if (point->clip(getMinPoint(), getMaxPoint()))
                        clippedDisplayFile.push_back(geometry);
                }
                break;
                case geometries::line:
                {
                    Line *line = dynamic_cast<Line*>(geometry);
                    if (line->clip(getMinPoint(), getMaxPoint()))
                        clippedDisplayFile.push_back(geometry);
                }
                break;
                case geometries::polygon:
                {
                    Polygon *polygon = dynamic_cast<Polygon*>(geometry);
                    if (polygon->clip(getMinPoint(), getMaxPoint()))
                        clippedDisplayFile.push_back(geometry);
                }
                break;
            }
        }
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
        return &world_min;
    }

    Coordinate *getMaxPoint()
    {
        return &world_max;
    }

    double WindowWidth(){
        return world_max.getX() - world_min.getX();
    }

    double WindowHeight(){
        return world_max.getY() - world_min.getY();
    }

    std::list<Geometry *> displayFile;
    std::list<Geometry *> clippedDisplayFile;

private:
    int pointCount = 1;
    int lineCount = 1;
    int polygonCount = 1;
    Coordinate world_min, world_max;
    Coordinate window_min = Coordinate(-1, -1);
    Coordinate window_max = Coordinate(1, 1);
    Coordinate v = Coordinate(0, 1);

    const Coordinate GetWindowCenter() {
        double xSum = 0.0;
        double ySum = 0.0;

        xSum += world_max.getX();
        ySum += world_max.getY();
        xSum += world_min.getX();
        ySum += world_min.getY();

        auto Cx = xSum / 2;
        auto Cy = ySum / 2;

        return Coordinate(Cx, Cy);
    }
};

#endif /* end of include guard: WINDOW_HPP_ */
