#pragma once

#ifndef VIEWPORT_HPP_
#define VIEWPORT_HPP_

#include <stdlib.h>
#include <iostream>
#include <list>

#include "Window.hpp"

int xMax, yMax;
cairo_t *cr;

class ViewPort {
public:
    ViewPort(Window *_window, int width, int height)
    {
        yMax = height;
        xMax = width;
        window = _window;

        std::cout << "* Debug " << yMax << ", " << xMax << std::endl;
    }

    ~ViewPort() {}

    void redraw() {
        cr = cairo_create (surface);
        cairo_set_source_rgb (cr, 1.0, 1.0, 1.0); /* blank to white */
        cairo_paint (cr);
        cairo_destroy (cr);

        std::list<Coordinate> transformedCoordinates;
        for(auto geometry : window->displayFile) {
            for(auto coordinate : geometry->coordinates) {
                transformedCoordinates.push_back(windowToViewport(coordinate));
            }
            draw(geometry->type, &transformedCoordinates);
            transformedCoordinates.clear();
        }
    }

    void draw(geometries::Type type, std::list<Coordinate> *coordinates) {
        cr = cairo_create(surface);

        switch (type) {
            case geometries::point:
            {
                Coordinate coordinate = coordinates->front();
                cairo_set_line_width(cr, 1);
                cairo_arc(cr, coordinate.getX(), coordinate.getY(), 1, 0, 10);
                cairo_stroke_preserve(cr);
                cairo_fill(cr);
                gtk_widget_queue_draw_area (drawing_area, 0 , 0, yMax, xMax);
                break;
            }
            default:
                std::list<Coordinate>::iterator nextCoord;
                for (std::list<Coordinate>::iterator it = coordinates->begin(); it != coordinates->end(); it++) {
                    if (std::next(it, 1) == coordinates->end())
                        nextCoord = coordinates->begin();
                    else
                        nextCoord = std::next(it, 1);

                    cairo_move_to(cr, (it)->getX(), (it)->getY());
                    cairo_line_to(cr, (nextCoord)->getX(), (nextCoord)->getY());
                }
                cairo_stroke(cr);
                gtk_widget_queue_draw_area (drawing_area, 0 , 0, yMax, xMax);
                break;
        }
    }

    Coordinate windowToViewport(Coordinate * pointOnWindow)
    {
        /**
        * Xvp = ((Xw - Xwmin) / (Xwmax - Xwmin)) * (Xvpmax - Xvpmin)
        */
        auto windowWidth = window->getMaxPoint()->getX() - window->getMinPoint()->getX();
        // auto viewPortWidth = width()/*maxVpPoint.getX() - minVpPoint.getX()*/;
        auto xvp = ((pointOnWindow->getX() - window->getMinPoint()->getX()) / (windowWidth)) * xMax;

        /**
        * Yvp = (1 - ((Yw - Ywmin) / (Ywmax - Ywmin))) * (Yvpmax - Yvpmin)
        */
        auto windowHeight = window->getMaxPoint()->getY() - window->getMinPoint()->getY();
        // auto viewPortHeight = height()/*maxVpPoint.getY() - minVpPoint.getY()*/;
        auto yvp = (1 - ((pointOnWindow->getY() - window->getMinPoint()->getY()) / (windowHeight))) * yMax;

        return Coordinate(xvp, yvp);
    }

private:
    int width()
    {
        return xMax;
    }

    int height()
    {
        return yMax;
    }

    Window * window;
};

/*Clear the surface, removing the scribbles*/
static void clear_surface (){
    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
}

/*Creates the surface*/
static gboolean create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
    if (surface)
        cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                                CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width (widget),
                                                gtk_widget_get_allocated_height (widget));

    xMax = gtk_widget_get_allocated_width (widget);
    yMax = gtk_widget_get_allocated_height (widget);

    clear_surface ();
    return TRUE;
}

/* Redraw the screen from the surface */
static gboolean redraw (GtkWidget *widget, cairo_t *cr, gpointer data){
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}

#endif /* end of include guard: VIEWPORT_HPP_ */
