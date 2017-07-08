#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cmath>

#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Bspline.hpp"
#include "Coordinate.hpp"
#include "Coordinate3D.hpp"

class Window {
public:
    Window(const Coordinate3D &_world_min, const Coordinate3D &_world_max)
    : world_min(_world_min)
    , world_max(_world_max)
    {
    }

    ~Window() { }

    void moveUp(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix3D(0, steps, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveDown(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix3D(0, steps * -1, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveLeft(int steps)
    {

        auto T_matrix = Transformation::TranslateMatrix3D(steps * -1, 0, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void moveRight(int steps)
    {
        auto T_matrix = Transformation::TranslateMatrix3D(steps, 0, 0);

        world_max.transform(T_matrix);
        world_min.transform(T_matrix);
    }

    void zoom(float Sx, float Sy, float Sz)
    {
        Coordinate3D center = GetWindowCenter();

        auto T_matrix1 = Transformation::TranslateMatrix3D(center.getX() * -1, center.getY() * -1, center.getZ() * -1);
        auto S_matrix = Transformation::ScalingMatrix3D(Sx, Sy, Sz);
        auto T_matrix2 = Transformation::TranslateMatrix3D(center.getX(), center.getY(), center.getZ());

        auto R_matrix = Transformation::matrixProduct4x4(Transformation::matrixProduct4x4(T_matrix1, S_matrix), T_matrix2);

        world_max.transform(R_matrix);
        world_min.transform(R_matrix);
    }

    void rotate(float _angle) {
        Coordinate3D center = GetWindowCenter();

        for (auto geometry : displayFile) {
            geometry->rotate(_angle * -1, true);
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
                case geometries::curve:
                {    
                    Bspline *curve = dynamic_cast<Bspline*>(geometry);
                    if (curve->clip(getMinPoint(), getMaxPoint()))
                        clippedDisplayFile.push_back(geometry);
                }
                break;
            }
        }
    }

    string AddPoint(std::list<Coordinate3D*> coordinates) {
        string name = "point_" + std::to_string(pointCount++);
        Geometry *point = new Point(geometries::point, name, coordinates);
        displayFile.push_back(point);

        return name;
    }

    string AddLine(std::list<Coordinate3D*> coordinates) {
        string name = "line_" + std::to_string(lineCount++);
        Geometry *line = new Line(geometries::line, name, coordinates);
        displayFile.push_back(line);

        return name;
    }

    string AddPolygon(std::list<Coordinate3D*> coordinates) {
        string name = "polygon_" + std::to_string(polygonCount++);
        Geometry *polygon = new Polygon(geometries::polygon, name, coordinates);
        displayFile.push_back(polygon);

        return name;
    }

    string AddCurve(std::list<Coordinate3D*> coordinates) {
        string name = "curve_" + std::to_string(curveCount++);
        Geometry *curve = new Bspline(geometries::curve, name, coordinates);
        displayFile.push_back(curve);

        return name;
    }

    Coordinate3D *getMinPoint()
    {
        return &world_min;
    }

    Coordinate3D *getMaxPoint()
    {
        return &world_max;
    }

    float WindowWidth(){
        return world_max.getX() - world_min.getX();
    }

    float WindowHeight(){
        return world_max.getY() - world_min.getY();
    }

    std::list<Geometry *> displayFile;
    std::list<Geometry *> clippedDisplayFile;

private:
    int pointCount = 1;
    int lineCount = 1;
    int polygonCount = 1;
    int curveCount = 1;
    Coordinate3D world_min, world_max;
    Coordinate3D *vpn = new Coordinate3D(0.0f, 0.0f, 1.0f);

    const Coordinate3D GetWindowCenter() {
        float xSum = 0.0;
        float ySum = 0.0;
        float zSum = 0.0;

        xSum += world_max.getX();
        ySum += world_max.getY();
        zSum += world_max.getZ();
        xSum += world_min.getX();
        ySum += world_min.getY();
        zSum += world_min.getZ();

        auto Cx = xSum / 2;
        auto Cy = ySum / 2;
        auto Cz = zSum / 2;

        return Coordinate3D(Cx, Cy, Cz);
    }
};

#endif /* end of include guard: WINDOW_HPP_ */
