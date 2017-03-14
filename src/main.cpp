#include <gtk/gtk.h>
#include "mainWindow.hpp"

int main(int argc, char *argv[]){

	gtk_init(&argc, &argv);
	UI::MainWindow w;
	return w.init();
}
