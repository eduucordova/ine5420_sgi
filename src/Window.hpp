#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Elemento.hpp"
#include "ListaEnc.hpp"
#include "Coordinate.hpp"

class Window {
public:
    Window(const Coordinate &_Wmin, const Coordinate &_Wmax)
    : Wmin(_Wmin)
    , Wmax(_Wmax)
    {
        // displayFile = new ListaEnc<Geometry *>();
    }

    ~Window() { }

    void AddPoint(Coordinate *coordinate) {

    }

private:
    const ListaEnc <Geometry *> *displayFile;
    Coordinate Wmin, Wmax;
};

#endif /* end of include guard: WINDOW_HPP_ */
