#pragma once

#ifndef VIEWPORT_HPP_
#define VIEWPORT_HPP_

#include <stdlib.h>
#include <iostream>
#include <list>

int xMax, yMax;
cairo_t *cr;

class ViewPort {
public:
    ViewPort(int width, int height)
    {
        xMax = height;
        yMax = width;
    }

    ~ViewPort() {}

    void draw(int type, std::list<Coordinate*> *coordinates) {
        cr = cairo_create(surface);

        switch (type) {
            case 0:
            {
                Coordinate *coordinate = coordinates->front();
                cairo_set_line_width(cr, 1);
                cairo_arc(cr, coordinate->getX(), coordinate->getY(), 1, 0, 10);
                cairo_stroke_preserve(cr);
                cairo_fill(cr);
                break;
            }
            case 1:
                std::list<Coordinate*>::iterator nextCoord;
                for (std::list<Coordinate*>::iterator it = coordinates->begin(); it != coordinates->end(); it++) {
                    if (std::next(it, 1) == coordinates->end())
                        nextCoord = coordinates->begin();
                    else
                        nextCoord = std::next(it, 1);

                    cairo_move_to(cr, (*it)->getX(), (*it)->getY());
                    cairo_line_to(cr, (*nextCoord)->getX(), (*nextCoord)->getY());
                }
                cairo_stroke(cr);
                gtk_widget_queue_draw_area (drawing_area, 0 , 0, yMax, xMax);
                break;
        }
    }
private:
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
