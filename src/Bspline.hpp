#pragma once

#ifndef BSPLINE_HPP_
#define BSPLINE_HPP_

#include "Geometry.hpp"

class Bspline : public Geometry {
public:
    using Geometry::Geometry;

    void FowardDifferences() {
        int i = 0;
        for (auto coordinate : world_coordinates) {
            int j = i > 3 ? 3 : i;

            GbsX[j][0] = coordinate->getX();
            GbsY[j][0] = coordinate->getY();

            if (i >= 3) {
                auto Cx = Transformation::matrixProduct4x1(Mbs, GbsX);
                auto Cy = Transformation::matrixProduct4x1(Mbs, GbsY);
            
                auto Dx = Transformation::matrixProduct4x1(E, Cx);
                auto Dy = Transformation::matrixProduct4x1(E, Cy);

                DesenhaCurvaFwdDiff(1/d1, Dx[0][0], Dx[1][0], Dx[2][0], Dx[3][0],
                                          Dy[0][0], Dy[1][0], Dy[2][0], Dy[3][0]);

                GbsX[0][0] = GbsX[1][0];
                GbsX[1][0] = GbsX[2][0];
                GbsX[2][0] = GbsX[3][0];

                GbsY[0][0] = GbsY[1][0];
                GbsY[1][0] = GbsY[2][0];
                GbsY[2][0] = GbsY[3][0];
            }
            i++;
        }
    }

    bool clip(Coordinate *_winMin, Coordinate *_winMax) {
        _minPoint->setX(_winMin->getX() + 10);
        _maxPoint->setX(_winMax->getX() - 10);
        _minPoint->setY(_winMin->getY() + 10);
        _maxPoint->setY(_winMax->getY() - 10);

        window_coordinates.clear();
        polygon_coordinates.clear();

        FowardDifferences();

        PolygonClipping();

        return true;
    }

private:
    Coordinate * _minPoint = new Coordinate(0, 0);
    Coordinate * _maxPoint = new Coordinate(0, 0);
    std::list<Coordinate *> polygon_coordinates;

    float d1 = 0.01;
    float d2 = d1 * d1;
    float d3 = d2 * d1; 
   
    std::vector<std::vector<float>> E = { {    0,    0,  0, 1 },
                                          {   d3,   d2, d1, 0 },
                                          { 6*d3, 2*d2,  0, 0 },
                                          { 6*d3,    0,  0, 0 } };

    std::vector<std::vector<float>> Mbs = { { -0.16666666666,           0.5,          -0.5, 0.16666666666 },
                                            {            0.5,            -1,           0.5,             0 },
                                            {           -0.5,             0,           0.5,             0 },
                                            {  0.16666666666, 0.66666666666, 0.16666666666,             0 } };


    std::vector<std::vector<float>> GbsX = { { 0 },
                                             { 0 },
                                             { 0 },
                                             { 0 } };

    std::vector<std::vector<float>> GbsY = { { 0 },
                                             { 0 },
                                             { 0 },
                                             { 0 } };

    void DesenhaCurvaFwdDiff(int n, float x, float deltaX, float delta2X, float delta3X,
                                    float y, float deltaY, float delta2Y, float delta3Y)
    {
        // cout << "DesenhaCurvaFwdDiff" << endl;
        int i = 1;
        float x_velho, y_velho;

        while (i < n) {
            i += 1;
            
            x_velho = x;
            y_velho = y;

            polygon_coordinates.push_back(new Coordinate(x_velho, y_velho));

            x += deltaX;
            deltaX += delta2X;
            delta2X += delta3X;

            y += deltaY;
            deltaY += delta2Y;
            delta2Y += delta3Y;

        }
        // window_coordinates.push_back(new Coordinate(x, y));
    }

    bool PolygonClipping() {
        auto previusPoint = polygon_coordinates.front();

        bool retorno = false;

        for (auto coordinate : polygon_coordinates)
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

#endif /* end of include guard: BSPLINE_HPP_ */