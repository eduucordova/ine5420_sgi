#pragma once

GtkBuilder   *gtkBuilder;
GtkWidget    *drawing_area;
GtkWidget    *window_widget;
GtkWidget    *window_add_figure;
GtkStatusbar *status_bar;
GtkEntry	* entry_ponto_x;
GtkEntry	* entry_ponto_y;
GtkEntry	* entry_ponto_x1;
GtkEntry	* entry_ponto_y1;
GtkEntry	* entry_ponto_x2;
GtkEntry	* entry_ponto_y2;
GtkEntry	* entry_ponto_x3;
GtkEntry	* entry_ponto_y3;

static cairo_surface_t *surface = NULL;
