#include "mainWindow.hpp"

GtkBuilder   *gtkBuilder;
GtkWidget    *drawing_area;
GtkWidget    *window_widget;
GtkWidget    *window_add_figure;
GtkStatusbar *status_bar;

int UI::MainWindow::init() {
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

    window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
    drawing_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));
    status_bar = GTK_STATUSBAR(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "actions_status"));
    window_add_figure = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "window_add_figure"));

    gtk_builder_connect_signals(gtkBuilder, NULL);
    gtk_widget_show_all(window_widget);

    gtk_main();

    return 0;
}

void btn_up_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "up");
	gtk_statusbar_push(status_bar, context_id, "up");
}

void btn_down_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "down");
	gtk_statusbar_push(status_bar, context_id, "down");
}

void btn_left_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "left");
	gtk_statusbar_push(status_bar, context_id, "left");
}

void btn_right_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "right");
	gtk_statusbar_push(status_bar, context_id, "right");
}

void btn_zoom_in_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "zoomm in");
	gtk_statusbar_push(status_bar, context_id, "zoom in");
}

void btn_zoom_out_clicked_cb(GtkWidget *button) {
	guint context_id = gtk_statusbar_get_context_id (status_bar, "zoom out");
	gtk_statusbar_push(status_bar, context_id, "zoom out");
}

void on_steps_button_change_value(GtkSpinButton *spinButton) {
	guint steps = gtk_spin_button_get_value(spinButton);
	guint context_id = gtk_statusbar_get_context_id(status_bar, "step");

	char str[15];
	sprintf(str, "steps changed to: %d", steps);
	gtk_statusbar_push(status_bar, context_id, str);
}

void on_btn_add_figure_clicked() {
	gtk_window_set_position(GTK_WINDOW(window_add_figure), GTK_WIN_POS_CENTER_ALWAYS );
	gtk_widget_show(window_add_figure);

	guint context_id = gtk_statusbar_get_context_id (status_bar, "window add figure open");
	gtk_statusbar_push(status_bar, context_id, "window add figure open");
}
