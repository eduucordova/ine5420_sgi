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
GtkEntry     *entry_ponto_x;
GtkEntry     *entry_ponto_y;
GtkEntry     *entry_ponto_x1;
GtkEntry     *entry_ponto_y1;
GtkEntry     *entry_ponto_x2;
GtkEntry     *entry_ponto_y2;
GtkEntry     *entry_ponto_x3;
GtkEntry     *entry_ponto_y3;
GtkEntry     *entry_ponto_x4;
GtkEntry     *entry_ponto_y4;

static cairo_surface_t *surface = NULL;
