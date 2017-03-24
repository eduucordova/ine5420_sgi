#pragma once

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <list>

#include "Commom.hpp"
#include "Point.hpp"
#include "Window.hpp"
#include "Viewport.hpp"

class ViewPort;
class Window;

ViewPort * viewPort;
Window * window;
GtkTreeIter iterObjectList;

std::list<Coordinate*> coordinates;

namespace UI {

    static void populateForDebug();
    static void store_figure(string name);

    class MainWindow {
    public:
        MainWindow() { }

        int init() {
            gtkBuilder = gtk_builder_new();

            gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

            window = new Window(Coordinate(0.0, 0.0), Coordinate(100.0, 100.0));

            window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
            drawing_area  = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));
            status_bar = GTK_STATUSBAR(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "actions_status"));
            
            tree_object_list = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "tree_objects_list"));
            object_list = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_list"));

            initObjectList();

            g_signal_connect (drawing_area, "draw", G_CALLBACK (redraw), NULL);
            g_signal_connect (drawing_area,"configure-event", G_CALLBACK (create_surface), NULL);

            gtk_builder_connect_signals(gtkBuilder, NULL);
            gtk_widget_show_all(window_widget);

            viewPort = new ViewPort(window, gtk_widget_get_allocated_width(drawing_area), gtk_widget_get_allocated_height(drawing_area));
            populateForDebug();
            viewPort->redraw();

            gtk_main();

            return 0;
        }

        void initObjectList(){
            GtkCellRenderer *renderer;
           
            renderer = gtk_cell_renderer_text_new ();

            gtk_tree_view_insert_column_with_attributes (
                tree_object_list, -1,      
                "Nome", renderer,
                "text", 0,
                NULL);

            gtk_tree_view_set_model (tree_object_list, GTK_TREE_MODEL (object_list));
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

    static void populateForDebug() {
            std::list<Coordinate*> coordinates;
            coordinates.push_back(new Coordinate(25, 25));
            coordinates.push_back(new Coordinate(32, 76));
            coordinates.push_back(new Coordinate(87, 69));
            coordinates.push_back(new Coordinate(92, 32));
            coordinates.push_back(new Coordinate(41, 46));
            
            string name = window->AddPolygon(coordinates);
            store_figure(name);
    }

    static void store_figure(const string name){
        const char *ascii_name = g_str_to_ascii (name.c_str(), NULL);
        printf("%s\n", ascii_name);
        gtk_list_store_append (object_list, &iterObjectList);;
        gtk_list_store_set(
            object_list, &iterObjectList, 
            0, ascii_name, 
            -1);

    }

    static void write_status(const char *msg){
        guint context_id = gtk_statusbar_get_context_id (status_bar, msg);
        gtk_statusbar_push(status_bar, context_id, msg);
    }
}

// MainWindow events
extern "C"
G_MODULE_EXPORT {
    void on_btn_up_clicked_cb(GtkWidget *button) {
        window->moveUp(10);
        viewPort->redraw();

        UI::write_status("up");
    }

    void on_btn_down_clicked_cb(GtkWidget *button) {
        window->moveDown(10);
        viewPort->redraw();

        UI::write_status("down");
    }

    void on_btn_left_clicked_cb(GtkWidget *button) {
        window->moveLeft(10);
        viewPort->redraw();

        UI::write_status("left");
    }

    void on_btn_right_clicked_cb(GtkWidget *button) {
        window->moveRight(10);
        viewPort->redraw();

        UI::write_status("right");
    }

    void on_btn_zoom_in_clicked_cb(GtkWidget *button) {
        window->zoom(-10);
        viewPort->redraw();

        UI::write_status("zoom in");
    }

    void on_btn_zoom_out_clicked_cb(GtkWidget *button) {
        window->zoom(10);
        viewPort->redraw();

        UI::write_status("zoom out");
    }

    void on_btn_rotate_left_clicked(GtkWidget *button) {
        viewPort->redraw();

        UI::write_status("rotate window left");
    }

    void on_btn_rotate_right_clicked(GtkWidget *button) {
        viewPort->redraw();

        UI::write_status("rotate window right");
    }

    void on_btn_add_figure_clicked() {
        UI::AddFigureWindow afw;
    	afw.init();

        gtk_window_set_position(GTK_WINDOW(window_add_figure), GTK_WIN_POS_CENTER_ALWAYS );
        gtk_widget_show(window_add_figure);

        UI::write_status("window add figure open");
    }

    void on_btn_obj_shrink_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->scaling(0.9, 0.9);
        viewPort->redraw();

        char str[255];
        sprintf(str, "shrinking object up: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_expand_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->scaling(1.1, 1.1);
        viewPort->redraw();

        char str[255];
        sprintf(str, "expanding object up: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_up_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->translate(0, 5);
        viewPort->redraw();

        char str[255];
        sprintf(str, "move object up: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_right_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->translate(5, 0);
        viewPort->redraw();

        char str[255];
        sprintf(str, "move object right: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_left_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->translate(-5, 0);
        viewPort->redraw();

        char str[255];
        sprintf(str, "move object left: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_down_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->translate(0, -5);
        viewPort->redraw();

        char str[255];
        sprintf(str, "move object down: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_rotate_right_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->rotate(10);
        viewPort->redraw();

        char str[255];
        sprintf(str, "rotate right object: %s", object->name.c_str());
        UI::write_status(str);
    }
    void on_btn_obj_rotate_left_clicked()
    {
        // TODO pegar objeto selecionado na TreeView
        auto object = window->displayFile.front();
        object->rotate(-10);
        viewPort->redraw();

        char str[255];
        sprintf(str, "rotate left object: %s", object->name.c_str());
        UI::write_status(str);
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
        if (!coordinates.empty())
            coordinates.clear();

        double x = atof(gtk_entry_get_text(entry_ponto_x));
        double y = atof(gtk_entry_get_text(entry_ponto_y));

        coordinates.push_back(new Coordinate(x, y));

        string name = window->AddPoint(coordinates);
        viewPort->redraw();

        coordinates.clear();

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        char str[50];
        sprintf(str, "point at: %f; %f", x, y);
        UI::write_status(str);
    }

    void on_btn_add_line_clicked() {
        if (!coordinates.empty())
            coordinates.clear();

        double x1 = atof(gtk_entry_get_text(entry_ponto_x1));
        double y1 = atof(gtk_entry_get_text(entry_ponto_y1));
        double x2 = atof(gtk_entry_get_text(entry_ponto_x2));
        double y2 = atof(gtk_entry_get_text(entry_ponto_y2));

        coordinates.push_back(new Coordinate(x1, y1));
        coordinates.push_back(new Coordinate(x2, y2));

        string name = window->AddLine(coordinates);
        viewPort->redraw();

        coordinates.clear();

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        char str[255];
        sprintf(str, "line from: %f; %f to %f; %f", x1, y1, x2, y2);
        UI::write_status(str);
    }

    void on_btn_add_coordenada_clicked() {
        double x3 = atof(gtk_entry_get_text(entry_ponto_x3));
        double y3 = atof(gtk_entry_get_text(entry_ponto_y3));

        coordinates.push_back(new Coordinate(x3, y3));

        char str[255];
        sprintf(str, "added coordinate at: %f; %f", x3, y3);
        UI::write_status(str);
    }

    void on_btn_add_polygon_clicked(){
        string name = window->AddPolygon(coordinates);
        viewPort->redraw();

        coordinates.clear();

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        UI::write_status("drawing polygon");
    }
}

#endif /* WINDOWS_HPP_ */
