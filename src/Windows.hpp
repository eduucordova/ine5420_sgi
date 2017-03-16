#pragma once

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_

#include <gtk/gtk.h>
#include "Commom.hpp"
#include "Point.hpp"

namespace UI {
    class MainWindow {
    public:
        MainWindow() { }

        int init() {
            gtkBuilder = gtk_builder_new();

            gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

            window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
            drawing_area  = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));
            status_bar = GTK_STATUSBAR(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "actions_status"));

            gtk_builder_connect_signals(gtkBuilder, NULL);
            gtk_widget_show_all(window_widget);

            gtk_main();

            return 0;
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
std::vector<Coordinate *> *auxCoord;
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
        // auxCoord->push_back(coord);
        //
        // Point *ponto = new Point("nome", auxCoord);

        gtk_widget_hide(window_add_figure);

        char str[50];
        sprintf(str, "point at: %f; %f", x, y);
        UI::write_status(str);
    }
}

#endif /* WINDOWS_HPP_ */
