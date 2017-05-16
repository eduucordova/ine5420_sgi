
#include <gtk/gtk.h>
#include "Windows.hpp"

#define PI 3.14159265

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	UI::MainWindow w;
	return w.init();
}
