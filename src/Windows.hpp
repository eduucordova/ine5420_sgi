#pragma once

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_

#include "Commom.hpp"
#include "Point.hpp"
#include "Window.hpp"
#include "Viewport.hpp"

#include <gtk/gtk.h>
#include <iostream>
#include <memory>

class ViewPort;
class Window;

ViewPort * viewPort;
Window * window;

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

namespace UI {
    class MainWindow {
    public:
        MainWindow() { }

        int init() {
            glob.count = 0;

            gtkBuilder = gtk_builder_new();

            gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

            window = new Window(Coordinate(-100.0, -100.0), Coordinate(100.0, 100.0));

            window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
            drawing_area  = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));
            status_bar = GTK_STATUSBAR(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "actions_status"));

            viewPort = new ViewPort(gtk_widget_get_allocated_width(drawing_area), gtk_widget_get_allocated_height(drawing_area));

            g_signal_connect (drawing_area, "draw", G_CALLBACK (redraw), NULL);
            g_signal_connect (drawing_area,"configure-event", G_CALLBACK (create_surface), NULL);

            gtk_builder_connect_signals(gtkBuilder, NULL);
            gtk_widget_show_all(window_widget);

            gtk_main();

            return 0;
        }

        /*Clear the surface, removing the scribbles*/
        static void clear_surface (){
          cairo_t *cr;

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
        static gboolean redraw (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
          cairo_set_source_surface (cr, surface, 0, 0);
          cairo_paint (cr);

          return FALSE;
        }
    };

    class AddFigureWindow {
    public:
        AddFigureWindow() { }

        int init() {
            window_add_figure = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "window_add_figure"));

            entry_ponto_x =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x"));
            entry_ponto_y =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y"));
            entry_ponto_x1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x1"));
            entry_ponto_y1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y1"));
            entry_ponto_x2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x2"));
            entry_ponto_y2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y2"));
            entry_ponto_x3 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x3"));
            entry_ponto_y3 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y3"));

            gtk_builder_connect_signals(gtkBuilder, NULL);

            return 0;
        }
    };

    static void write_status(const char *msg){
        guint context_id = gtk_statusbar_get_context_id (status_bar, msg);
        gtk_statusbar_push(status_bar, context_id, msg);
    }
}

#include <stdlib.h>
#include <iostream>
#include <vector>

// MainWindow events
extern "C"
G_MODULE_EXPORT {
    void on_btn_up_clicked_cb(GtkWidget *button) {
        UI::write_status("up");
    }

    void on_btn_down_clicked_cb(GtkWidget *button) {
        UI::write_status("down");
    }

    void on_btn_left_clicked_cb(GtkWidget *button) {
        UI::write_status("left");
    }

    void on_btn_right_clicked_cb(GtkWidget *button) {
        UI::write_status("right");
    }

    void on_btn_zoom_in_clicked_cb(GtkWidget *button) {
        UI::write_status("zoom in");
    }

    void on_btn_zoom_out_clicked_cb(GtkWidget *button) {
        UI::write_status("zoom out");
    }

    void on_steps_button_change_value(GtkSpinButton *spinButton) {

        char str[20];
        guint steps = gtk_spin_button_get_value(spinButton);
        sprintf(str, "steps changed to: %d", steps);
        UI::write_status(str);
    }

    void on_btn_add_figure_clicked() {
        UI::AddFigureWindow afw;
    	afw.init();

        gtk_window_set_position(GTK_WINDOW(window_add_figure), GTK_WIN_POS_CENTER_ALWAYS );
        gtk_widget_show(window_add_figure);

        UI::write_status("window add figure open");
    }
}




// AddFigureWindow EVENTS_HPP_
extern "C"
G_MODULE_EXPORT {
    void on_btn_close_clicked() {
        gtk_widget_hide(window_add_figure);
        UI::write_status("window add figure close");
    }

    void on_btn_add_point_clicked() {
        double x = atof(gtk_entry_get_text(entry_ponto_x));
        double y = atof(gtk_entry_get_text(entry_ponto_y));

        // Coordinate *coord = new Coordinate(x, y);
        //
        // window->AddPoint(coord);
        cairo_t *cr;

      	cr = cairo_create(surface);

      	cairo_set_line_width(cr, 1);
      	cairo_arc(cr, x, y, 1, 0, 10);
      	cairo_stroke_preserve(cr);
      	cairo_fill(cr);

    	 cairo_destroy(cr);

        gtk_widget_queue_draw_area(drawing_area, 0 , 0, 900, 900);

        gtk_widget_hide(window_add_figure);

        char str[50];
        sprintf(str, "point at: %f; %f", x, y);
        UI::write_status(str);
    }

    void on_btn_add_line_clicked() {
        double x1 = atof(gtk_entry_get_text(entry_ponto_x1));
        double y1 = atof(gtk_entry_get_text(entry_ponto_y1));
        double x2 = atof(gtk_entry_get_text(entry_ponto_x2));
        double y2 = atof(gtk_entry_get_text(entry_ponto_y2));

        cairo_t *cr;
        cr = cairo_create (surface);
        cairo_move_to(cr, x1, y1);
        cairo_line_to(cr, x2, y2);
        cairo_stroke(cr);
        gtk_widget_queue_draw_area (drawing_area, 0 , 0, 900, 900);

        gtk_widget_hide(window_add_figure);

        char str[50];
        sprintf(str, "line from: %f; %f to %f; %f", x1, y1, x2, y2);
        UI::write_status(str);
    }

    void on_btn_add_coordenada_clicked() {
        double x3 = atof(gtk_entry_get_text(entry_ponto_x3));
        double y3 = atof(gtk_entry_get_text(entry_ponto_y3));
        glob.coordx[glob.count] = x3;
        glob.coordy[glob.count++] = y3;

        char str[50];
        sprintf(str, "added coordinate at: %f; %f", x3, y3);
        UI::write_status(str);
    }

    void on_btn_add_polygon_clicked(){
        cairo_t *cr;
        cr = cairo_create (surface);

        int i, j;
        for(i = 0; i <= glob.count - 1; i++) {
            if(i < glob.count - 1)
                j = i + 1;
            else
                j = 0;
            cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
            cairo_line_to(cr, glob.coordx[j], glob.coordy[j]);
        }

        glob.count = 0;
        cairo_stroke(cr);
        gtk_widget_queue_draw_area (drawing_area, 0 , 0, 900, 900);

        gtk_widget_hide(window_add_figure);
    }
}

#endif /* WINDOWS_HPP_ */
