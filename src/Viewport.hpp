#pragma once

#ifndef VIEWPORT_HPP_
#define VIEWPORT_HPP_

class ViewPort {
public:
    ViewPort(int width, int height)
    : xMax(height)
    , yMax(width)
    {

    }

    ~ViewPort() {}


private:
    int xMax, yMax;
};

#endif /* end of include guard: VIEWPORT_HPP_ */
