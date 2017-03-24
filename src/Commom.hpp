#pragma once

GtkBuilder   *gtkBuilder;
GtkWidget    *drawing_area;
GtkWidget    *window_widget;
GtkWidget    *window_add_figure;
GtkStatusbar *status_bar;
GtkTreeView  *tree_object_list;
GtkListStore *object_list;
GtkEntry	 *entry_ponto_x;
GtkEntry	 *entry_ponto_y;
GtkEntry	 *entry_ponto_x1;
GtkEntry	 *entry_ponto_y1;
GtkEntry	 *entry_ponto_x2;
GtkEntry	 *entry_ponto_y2;
GtkEntry	 *entry_ponto_x3;
GtkEntry	 *entry_ponto_y3;

GtkTreeIter iter;

static cairo_surface_t *surface = NULL;
