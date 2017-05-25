#pragma once

#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

#include <cmath>
#include <iostream>
#include <vector>

namespace Transformation {
    std::vector<std::vector<float>> TranslateMatrix(float dx, float dy)
    {
        std::vector<std::vector<float>> translateMatrix = { {  1,  0, 0 },
                                                            {  0,  1, 0 },
                                                            { dx, dy, 1 } };

       return translateMatrix;
    }

    std::vector<std::vector<float>> ScalingMatrix(float sx, float sy)
    {
        std::vector<std::vector<float>> scalingMatrix = { { sx,  0, 0 },
                                                          {  0, sy, 0 },
                                                          {  0,  0, 1 } };

        return scalingMatrix;
    }

    std::vector<std::vector<float>> RotateMatrix(float angle)
    {
        float radiansAngle = angle * static_cast<float>(M_PI) / 180.f;
        float _cos = cos(radiansAngle);
        float _sin = sin(radiansAngle);

        std::vector<std::vector<float>> rotateMatrix = { { _cos, -_sin, 0 },
                                                         { _sin,  _cos, 0 },
                                                         {    0,     0, 1 } };

        return rotateMatrix;
    }

    std::vector<std::vector<float>> TranslateMatrix3D(float dx, float dy, float dz)
    {
        std::vector<std::vector<float>> translateMatrix = { {  1,  0,  0,  0 },
                                                            {  0,  1,  0,  0 },
                                                            {  0,  0,  1,  0 },
                                                            { dx, dy, dz,  1 } };

       return translateMatrix;
    }

    std::vector<std::vector<float>> ScalingMatrix3D(float sx, float sy, float sz)
    {
        std::vector<std::vector<float>> scalingMatrix = { { sx,  0, 0,  0 },
                                                          {  0, sy, 0,  0 },
                                                          {  0,  0, sz, 0},
                                                          {  0,  0,  0, 1 } };

        return scalingMatrix;
    }

    std::vector<std::vector<float>> RotateMatrix3Dx(float _cos, float _sin)
    {
        std::vector<std::vector<float>> rotateMatrix = { { 1,    0,     0, 0 },
                                                         { 0,  _cos, _sin, 0 },
                                                         { 0, -_sin, _cos, 0 },
                                                         { 0,     0,    0, 1 } };

        return rotateMatrix;
    }

    std::vector<std::vector<float>> RotateMatrix3Dy(float _cos, float _sin)
    {
        std::vector<std::vector<float>> rotateMatrix = { { _cos, 0, -_sin, 0 },
                                                         {    0, 1,     0, 0 },
                                                         { _sin, 0,  _cos, 0 },
                                                         {    0, 0,     0, 1 } };

        return rotateMatrix;
    }

    std::vector<std::vector<float>> RotateMatrix3Dz(float angle)
    {
        float radiansAngle = angle * static_cast<float>(M_PI) / 180.f;
        float _cos = cos(radiansAngle);
        float _sin = sin(radiansAngle);

        std::vector<std::vector<float>> rotateMatrix = { {  _cos, _sin, 0, 0 },
                                                         { -_sin, _cos, 0, 0 },
                                                         {     0,    0, 1, 0 },
                                                         {     0,    0, 0, 1 } };;

        return rotateMatrix;
    }

    std::vector<std::vector<float>> matrixProduct3x3(
        const std::vector<std::vector<float>>& A_matrix,
        const std::vector<std::vector<float>>& B_matrix)
    {
        std::vector<std::vector<float>> newVec = { { 0, 0, 0 },
                                                   { 0, 0, 0 },
                                                   { 0, 0, 0 } };

        for (std::size_t i = 0; i < A_matrix.size(); ++i)
        {
            for (std::size_t j = 0; j < B_matrix[i].size(); ++j)
            {
                for(std::size_t k = 0; k < A_matrix.size(); ++k)
                {
                    newVec[i][j] += A_matrix[i][k] * B_matrix[k][j];
                }
            }
        }

        return newVec;
    }

    std::vector<std::vector<float>> matrixProduct4x1(
        const std::vector<std::vector<float>>& A_matrix,
        const std::vector<std::vector<float>>& B_matrix)
    {
        std::vector<std::vector<float>> newVec = { { 0 },
                                                   { 0 },
                                                   { 0 },
                                                   { 0 } };

        for (std::size_t i = 0; i < A_matrix.size(); i++)
        {
            for (std::size_t j = 0; j < B_matrix[i].size(); j++)
            {
                for(std::size_t k = 0; k < A_matrix.size(); k++)
                {
                    newVec[i][j] += A_matrix[i][k] * B_matrix[k][j];
                }
            }
        }

        return newVec;
    }

    std::vector<std::vector<float>> matrixProduct4x2(
        const std::vector<std::vector<float>>& A_matrix,
        const std::vector<std::vector<float>>& B_matrix)
    {
        std::vector<std::vector<float>> newVec = { { 0, 0 },
                                                   { 0, 0 },
                                                   { 0, 0 },
                                                   { 0, 0 } };

        for (std::size_t i = 0; i < A_matrix.size(); ++i)
        {
            for (std::size_t j = 0; j < B_matrix[i].size(); ++j)
            {
                for(std::size_t k = 0; k < A_matrix.size(); ++k)
                {
                    newVec[i][j] += A_matrix[i][k] * B_matrix[k][j];
                }
            }
        }

        return newVec;
    }

    std::vector<std::vector<float>> matrixProduct4x4(
        const std::vector<std::vector<float>>& A_matrix,
        const std::vector<std::vector<float>>& B_matrix)
    {
        std::vector<std::vector<float>> newVec = { { 0,0,0,0 },
                                                   { 0,0,0,0 },
                                                   { 0,0,0,0 },
                                                   { 0,0,0,0 } };

        for (std::size_t i = 0; i < A_matrix.size(); ++i)
        {
            for (std::size_t j = 0; j < B_matrix[i].size(); ++j)
            {
                for(std::size_t k = 0; k < A_matrix.size(); ++k)
                {
                    newVec[i][j] += A_matrix[i][k] * B_matrix[k][j];
                }
            }
        }

        return newVec;
    }

    int printMatrix(const std::vector<std::vector<float>>& matrix) {
        for (std::size_t i = 0; i < matrix.size(); i++) {
            for (std::size_t j = 0; j < matrix[i].size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        return 1;
    }
}

#endif /* end of include guard: TRANSFORMATION_HPP_ */
