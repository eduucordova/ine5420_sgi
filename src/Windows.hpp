#pragma once

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <glib-object.h>

#include "Commom.hpp"
#include "Point.hpp"
#include "Window.hpp"
#include "Viewport.hpp"

class ViewPort;
class Window;

ViewPort * viewPort;
Window * window;
GtkTreeIter iterObjectList;
GtkTreeIter iterCoordList;
GtkTreeSelection * object_selection;
Geometry *selected_object;

std::list<Coordinate3D*> coordinates;

namespace UI {

    static void populateForDebug();
    static void store_figure(string name);

    class MainWindow {
    public:
        MainWindow() { }

        int init() {
            gtkBuilder = gtk_builder_new();

            gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

            window = new Window(Coordinate(-100.0, -100.0), Coordinate(100.0, 100.0));

            window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
            drawing_area  = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));
            status_bar = GTK_STATUSBAR(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "actions_status"));
            
            tree_object_list = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "tree_objects_list"));
            object_list = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_list"));
            initObjectList();

            tree_polygon_coordinates = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "tree_polygon_coordinates"));
            polygon_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "polygon_coordinates"));
            initCoordinteList();

            tree_curve_coordinates = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "tree_curve_coordinates"));
            curve_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "curve_coordinates"));
            initCurveCoordinteList();

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

            object_selection = gtk_tree_view_get_selection(tree_object_list);
        }

        void initCoordinteList(){
            GtkCellRenderer *renderer;
           
            renderer = gtk_cell_renderer_text_new ();

            gtk_tree_view_insert_column_with_attributes (
                tree_polygon_coordinates, -1,      
                "Coordinates", renderer,
                "text", 0,
                NULL);

            gtk_tree_view_set_model (tree_polygon_coordinates, GTK_TREE_MODEL (polygon_coordinates));
        }

        void initCurveCoordinteList(){
            GtkCellRenderer *renderer;
           
            renderer = gtk_cell_renderer_text_new ();

            gtk_tree_view_insert_column_with_attributes (
                tree_curve_coordinates, -1,      
                "Coordinates", renderer,
                "text", 0,
                NULL);

            gtk_tree_view_set_model (tree_curve_coordinates, GTK_TREE_MODEL (curve_coordinates));
        }
    };

    class AddFigureWindow {
    public:
        AddFigureWindow() { }

        int init() {
            window_add_figure = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "window_add_figure"));

            entry_ponto_x =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x"));
            entry_ponto_y =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y"));
            // entry_ponto_z =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_z"));
            entry_ponto_x1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x1"));
            entry_ponto_y1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y1"));
            // entry_ponto_z1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_z1"));
            entry_ponto_x2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x2"));
            entry_ponto_y2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y2"));
            // entry_ponto_z2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_z2"));
            entry_ponto_x3 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x3"));
            entry_ponto_y3 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y3"));
            // entry_ponto_z3 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_z3"));
            entry_ponto_x4 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_x4"));
            entry_ponto_y4 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_y4"));
            // entry_ponto_z4 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_ponto_z4"));

            gtk_builder_connect_signals(gtkBuilder, NULL);

            return 0;
        }
    };

    static void populateForDebug() {
            std::list<Coordinate3D*> coordinates;
            string name = "";
            coordinates.push_back(new Coordinate3D( 0, -30, 0));
            coordinates.push_back(new Coordinate3D( 30,-15, 0));
            coordinates.push_back(new Coordinate3D( 30, 15, 0));
            coordinates.push_back(new Coordinate3D( 0,  30, 0));
            coordinates.push_back(new Coordinate3D(-30, 15, 0));
            coordinates.push_back(new Coordinate3D(-30,-15, 0));
            coordinates.push_back(new Coordinate3D( 0, -30, 0));
            
            name = window->AddPolygon(coordinates);
            store_figure(name);

            coordinates.clear();
            coordinates.push_back(new Coordinate3D(0,  100, 0));
            coordinates.push_back(new Coordinate3D(0, -100, 0));
            name = window->AddLine(coordinates);
            store_figure(name);

            coordinates.clear();
            coordinates.push_back(new Coordinate3D( 100, 0, 0));
            coordinates.push_back(new Coordinate3D(-100, 0, 0));
            name = window->AddLine(coordinates);
            store_figure(name);

            coordinates.clear();
            coordinates.push_back(new Coordinate3D(  0, -30, 0));
            coordinates.push_back(new Coordinate3D( 30, -15, 0));
            coordinates.push_back(new Coordinate3D( 30,  15, 0));
            coordinates.push_back(new Coordinate3D(  0,  30, 0));
            coordinates.push_back(new Coordinate3D(-30,  15, 0));
            coordinates.push_back(new Coordinate3D(-30, -15, 0));
            coordinates.push_back(new Coordinate3D(  0, -30, 0));
            coordinates.push_back(new Coordinate3D( 30, -15, 0));
            coordinates.push_back(new Coordinate3D( 30,  15, 0));
            coordinates.push_back(new Coordinate3D(  0,  30, 0));
            name = window->AddCurve(coordinates);
            store_figure(name);
    }

    static void store_figure(const string name){
        const char *ascii_name = name.c_str();
        gtk_list_store_append (object_list, &iterObjectList);;
        gtk_list_store_set(
            object_list, &iterObjectList, 
            0, ascii_name, 
            -1);
    }

    static void store_coordinate(Coordinate3D *coordinate){
        char coord[50];
        sprintf(coord, "x: %f; y: %f; z: %f", coordinate->getX(), coordinate->getY(), coordinate->getZ());
        gtk_list_store_append (polygon_coordinates, &iterCoordList);
        gtk_list_store_set(
            polygon_coordinates, &iterCoordList, 
            0, coord,
            -1);
    }

    static void store_curve_coordinate(Coordinate3D *coordinate){
        char coord[50];
        sprintf(coord, "x: %f; y: %f; z: %f", coordinate->getX(), coordinate->getY(), coordinate->getZ());
        gtk_list_store_append (curve_coordinates, &iterCoordList);
        gtk_list_store_set(
            curve_coordinates, &iterCoordList, 
            0, coord,
            -1);
    }

    static void write_status(const char *msg){
        guint context_id = gtk_statusbar_get_context_id (status_bar, msg);
        gtk_statusbar_push(status_bar, context_id, msg);
    }

    static bool get_selected_object()
    {
        auto model = GTK_TREE_MODEL(object_list);
        GValue value = G_VALUE_INIT;
        gtk_tree_selection_get_selected(object_selection, NULL, &iterObjectList);

        if(gtk_list_store_iter_is_valid(object_list, &iterObjectList)) {
            gtk_tree_model_get_value (model, &iterObjectList, 0, &value);
    
            for(auto geometry : window->displayFile)
            {
                if(geometry->name == g_value_get_string(&value))
                {
                    selected_object = geometry;
                    g_value_unset(&value);
                    return true;
                }
            }
        }

        return false;
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
        window->zoom(0.85, 0.85);
        viewPort->redraw();

        UI::write_status("zoom in");
    }

    void on_btn_zoom_out_clicked_cb(GtkWidget *button) {
        window->zoom(1.15, 1.15);
        viewPort->redraw();

        UI::write_status("zoom out");
    }

    void on_btn_rotate_left_clicked(GtkWidget *button) {
        window->rotate(-45);
        viewPort->redraw();

        UI::write_status("rotate window left");
    }

    void on_btn_rotate_right_clicked(GtkWidget *button) {
        window->rotate(45);
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
        if(UI::get_selected_object()) {

            selected_object->scaling(0.9, 0.9, 0.9);
            viewPort->redraw();

            char str[255];
            sprintf(str, "shrinking object: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_expand_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->scaling(1.1, 1.1, 1.1);
            viewPort->redraw();

            char str[255];
            sprintf(str, "expanding object: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_up_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->translate(0, 5, 0);
            viewPort->redraw();

            char str[255];
            sprintf(str, "move object up: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_right_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->translate(5, 0, 0);
            viewPort->redraw();

            char str[255];
            sprintf(str, "move object right: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_left_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->translate(-5, 0, 0);
            viewPort->redraw();

            char str[255];
            sprintf(str, "move object left: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_down_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->translate(0, -5, 0);
            viewPort->redraw();

            char str[255];
            sprintf(str, "move object down: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_rotate_right_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->rotate(10);
            viewPort->redraw();

            char str[255];
            sprintf(str, "rotate right object: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
    }

    void on_btn_obj_rotate_left_clicked()
    {
        if(UI::get_selected_object()) {

            selected_object->rotate(-10);
            viewPort->redraw();

            char str[255];
            sprintf(str, "rotate left object: %s", selected_object->name.c_str());
            UI::write_status(str);
        }
        else
            UI::write_status("No objects selected.");
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

        float x = atof(gtk_entry_get_text(entry_ponto_x));
        float y = atof(gtk_entry_get_text(entry_ponto_y));
        // float z = atof(gtk_entry_get_text(entry_ponto_z));
        float z = 0.0f;

        coordinates.push_back(new Coordinate3D(x, y, z));

        string name = window->AddPoint(coordinates);
        viewPort->redraw();

        coordinates.clear();

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        char str[50];
        sprintf(str, "point at: %f; %f; %f", x, y, z);
        UI::write_status(str);
    }

    void on_btn_add_line_clicked() {
        if (!coordinates.empty())
            coordinates.clear();

        float x1 = atof(gtk_entry_get_text(entry_ponto_x1));
        float y1 = atof(gtk_entry_get_text(entry_ponto_y1));
        // float z1 = atof(gtk_entry_get_text(entry_ponto_z1));
        float z1 = 0.0f;
        float x2 = atof(gtk_entry_get_text(entry_ponto_x2));
        float y2 = atof(gtk_entry_get_text(entry_ponto_y2));
        // float z2 = atof(gtk_entry_get_text(entry_ponto_z2));
        float z2 = 0.0f;

        coordinates.push_back(new Coordinate3D(x1, y1, z1));
        coordinates.push_back(new Coordinate3D(x2, y2, z2));

        string name = window->AddLine(coordinates);
        viewPort->redraw();

        coordinates.clear();

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        char str[255];
        sprintf(str, "line from: %f; %f; %f to %f; %f; %f", x1, y1, z1, x2, y2, z2);
        UI::write_status(str);
    }

    void on_btn_add_coordenada_clicked() {
        float x3 = atof(gtk_entry_get_text(entry_ponto_x3));
        float y3 = atof(gtk_entry_get_text(entry_ponto_y3));
        // float z3 = atof(gtk_entry_get_text(entry_ponto_z3));
        float z3 = 0.0f;

        Coordinate3D *temp = new Coordinate3D(x3, y3, z3);
        UI::store_coordinate(temp);
        coordinates.push_back(temp);

        char str[255];
        sprintf(str, "added coordinate at: %f; %f; %f", x3, y3, z3);
        UI::write_status(str);
    }

    void on_btn_add_polygon_clicked(){
        string name = window->AddPolygon(coordinates);
        viewPort->redraw();

        coordinates.clear();
        gtk_list_store_clear(polygon_coordinates);

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        UI::write_status("drawing polygon");
    }

    void on_btn_add_curve_coordenada_clicked() {
        float x4 = atof(gtk_entry_get_text(entry_ponto_x4));
        float y4 = atof(gtk_entry_get_text(entry_ponto_y4));
        // float z4 = atof(gtk_entry_get_text(entry_ponto_z4));
        float z4 = 0.0f;

        Coordinate3D *temp = new Coordinate3D(x4, y4, z4);
        UI::store_curve_coordinate(temp);
        coordinates.push_back(temp);

        char str[255];
        sprintf(str, "added coordinate at: %f; %f; %f", x4, y4, z4);
        UI::write_status(str);
    }

    void on_btn_add_curve_clicked(){
        string name = window->AddCurve(coordinates);
        viewPort->redraw();

        coordinates.clear();
        gtk_list_store_clear(curve_coordinates);

        gtk_widget_hide(window_add_figure);

        UI::store_figure(name);

        UI::write_status("drawing polygon");
    }
}

#endif /* WINDOWS_HPP_ */
