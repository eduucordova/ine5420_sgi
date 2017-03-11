#include <gtk/gtk.h>
#include <iostream>
#include <vector>

GtkBuilder *gtkBuilder;
GtkWidget  *drawing_area;
GtkWidget  *window_widget;

extern "C" G_MODULE_EXPORT {

	void btn_up_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "up");
	}

	void btn_down_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "down");
	}

	void btn_left_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "left");
	}

	void btn_right_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "right");
	}

	void btn_zoom_in_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "zoom in");
	}

	void btn_zoom_out_clicked_cb(GtkWidget *button, GtkWidget *status) {
		gtk_statusbar_push(GTK_STATUSBAR(status), 1, "zoom out");
	}

}
int main(int argc, char *argv[]){

  gtk_init(&argc, &argv);

  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

  window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawing_area"));


  gtk_builder_connect_signals(gtkBuilder, NULL);
  gtk_widget_show_all(window_widget);

  gtk_main();

  return 0;
}


