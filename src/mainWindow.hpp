#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <gtk/gtk.h>

namespace UI {
    class MainWindow {
        public:
            MainWindow() { }

            int init();
    };
}

extern "C"
G_MODULE_EXPORT {
    void btn_up_clicked_cb(GtkWidget *button);

    void btn_down_clicked_cb(GtkWidget *button);

    void btn_left_clicked_cb(GtkWidget *button);

    void btn_right_clicked_cb(GtkWidget *button);

    void btn_zoom_in_clicked_cb(GtkWidget *button);

    void btn_zoom_out_clicked_cb(GtkWidget *button);

    void on_steps_button_change_value(GtkSpinButton *spinButton);

    void on_btn_add_figure_clicked();
}

#endif /* MAINWINDOW_HPP_ */
