#pragma once

GtkBuilder   *gtkBuilder;
GtkWidget    *drawing_area;
GtkWidget    *window_widget;
GtkWidget    *window_add_figure;
GtkStatusbar *status_bar;
GtkTreeView  *tree_object_list;
GtkListStore *object_list;
GtkTreeView  *tree_polygon_coordinates;
GtkListStore *polygon_coordinates;
GtkTreeView  *tree_curve_coordinates;
GtkListStore *curve_coordinates;
GtkEntry     *entry_point_x;
GtkEntry     *entry_point_y;
GtkEntry     *entry_point_z;
GtkEntry     *entry_point_x1;
GtkEntry     *entry_point_y1;
GtkEntry     *entry_point_z1;
GtkEntry     *entry_point_x2;
GtkEntry     *entry_point_y2;
GtkEntry     *entry_point_z2;
GtkEntry     *entry_point_x3;
GtkEntry     *entry_point_y3;
GtkEntry     *entry_point_z3;
GtkEntry     *entry_point_x4;
GtkEntry     *entry_point_y4;
GtkEntry     *entry_point_z4;

static cairo_surface_t *surface = NULL;
