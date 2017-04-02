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
    Window(const Coordinate &_Wmin, const Coordinate &_Wmax)
    : Wmin(_Wmin)
    , Wmax(_Wmax)
    , angle(0)
    {
        W1.setX(Wmin.getX());
        W1.setY(Wmax.getY());
        W2.setX(Wmax.getX());
        W2.setY(Wmin.getY());

        GeneratePPC();
    }

    ~Window() { }

    void moveUp(int steps)
    {
        Wmax.updateY(steps);
        Wmin.updateY(steps);
        W1.updateY(steps);
        W2.updateY(steps);

        PPCmax.updateY(steps);
        PPCmin.updateY(steps);
        PPCw1.updateY(steps);
        PPCw2.updateY(steps);
    }

    void moveDown(int steps)
    {
        Wmax.updateY(-1 * steps);
        Wmin.updateY(-1 * steps);
        W1.updateY(-1 * steps);
        W2.updateY(-1 * steps);

        PPCmax.updateY(-1 * steps);
        PPCmin.updateY(-1 * steps);
        PPCw1.updateY(-1 * steps);
        PPCw2.updateY(-1 * steps);
    }

    void moveLeft(int steps)
    {
        Wmax.updateX(-1 * steps);
        Wmin.updateX(-1 * steps);
        W1.updateX(-1 * steps);
        W2.updateX(-1 * steps);

        PPCmax.updateX(-1 * steps);
        PPCmin.updateX(-1 * steps);
        PPCw1.updateX(-1 * steps);
        PPCw2.updateX(-1 * steps);
    }

    void moveRight(int steps)
    {
        Wmax.updateX(steps);
        Wmin.updateX(steps);
        W1.updateX(steps);
        W2.updateX(steps);

        PPCmax.updateX(steps);
        PPCmin.updateX(steps);
        PPCw1.updateX(steps);
        PPCw2.updateX(steps);
    }

    void zoom(double size)
    {
        Wmax.updateX(size);
        Wmax.updateY(size);
        Wmin.updateX(size);
        Wmin.updateY(size);
        W1.updateX(size);
        W1.updateY(size);
        W2.updateX(size);
        W2.updateY(size);

        PPCmax.updateX(size);
        PPCmax.updateY(size);
        PPCmin.updateX(size);
        PPCmin.updateY(size);
        PPCw1.updateX(size);
        PPCw1.updateY(size);
        PPCw2.updateX(size);
        PPCw2.updateY(size);
    }

    void rotate(float _angle) {
        Coordinate center = GetWindowCenter();

        auto T_matrix1 = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);
        auto R_matrix = Transformation::RotateMatrix(_angle);
        auto T_matrix2 = Transformation::TranslateMatrix(center.getX(), center.getY());

        auto result = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, R_matrix), T_matrix2);

        Wmax.transform(result);
        Wmin.transform(result);
        W1.transform(result);
        W2.transform(result);

        GeneratePPC();
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
        return &PPCmin;
    }

    Coordinate *getMaxPoint()
    {
        return &PPCmax;
    }

    double WindowWidth() {
        return sqrt(pow((W2.getX() - PPCmin.getX()), 2) + pow((W2.getY() - PPCmin.getY()), 2));
    }

    double WindowHeight() {
        return sqrt(pow(W1.getX() - PPCmin.getX(), 2) + pow(W1.getY() - PPCmin.getY(), 2));
    }

    std::list<Geometry *> displayFile;
private:
    int pointCount = 1;
    int lineCount = 1;
    int polygonCount = 1;
    Coordinate W1 = Coordinate(0,0);
    Coordinate W2 = Coordinate(0,0);
    Coordinate Vu = Coordinate(0,0);
    Coordinate PPCmin = Coordinate(0,0);
    Coordinate PPCmax = Coordinate(0,0);
    Coordinate PPCw1 = Coordinate(0,0);
    Coordinate PPCw2 = Coordinate(0,0);
    Coordinate Wmin, Wmax;
    float angle;

    const Coordinate GetWindowCenter() {
        double xSum = 0.0;
        double ySum = 0.0;

        xSum += Wmax.getX();
        ySum += Wmax.getY();
        xSum += Wmin.getX();
        ySum += Wmin.getY();
        xSum += W1.getX();
        ySum += W1.getY();
        xSum += W2.getX();
        ySum += W2.getY();

        auto Cx = xSum / 4;
        auto Cy = ySum / 4;

        return Coordinate(Cx, Cy);
    }

    void GeneratePPC() {
        Coordinate center = GetWindowCenter();

        // auto T_matrix = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);

        Vu.setX(W1.getX() - Wmin.getX());
        Vu.setY(W1.getY() - Wmin.getY());

        angle = Vu.angle();

        if (angle < 0)
            angle += 360;

        // auto R_matrix = Transformation::RotateMatrix(-1*angle);
        
        // auto result = Transformation::matrixProduct(T_matrix, R_matrix);

        auto T_matrix1 = Transformation::TranslateMatrix(center.getX() * -1, center.getY() * -1);
        auto R_matrix = Transformation::RotateMatrix(-1*angle);
        auto T_matrix2 = Transformation::TranslateMatrix(center.getX(), center.getY());

        auto result = Transformation::matrixProduct(Transformation::matrixProduct(T_matrix1, R_matrix), T_matrix2);

        PPCmax = Wmax;
        PPCmin = Wmin;
        PPCw1 = W1;
        PPCw2 = W2;

        Wmax.transform(result);
        Wmin.transform(result);
        W1.transform(result);
        W2.transform(result);

        PPCmax.transform(result);
        PPCmin.transform(result);
        PPCw1.transform(result);
        PPCw2.transform(result);

        for(auto geometry : displayFile) {
            for(auto coordinate : geometry->ppcCoordinates) {
                coordinate->transform(result);
            }
        }
    }
};

#endif /* end of include guard: WINDOW_HPP_ */
