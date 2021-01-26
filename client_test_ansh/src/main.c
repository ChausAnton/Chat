#include "Chat.h"


int main(int argc, char *argv[]) {
    GtkWidget *window;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), window_size_x, window_size_y);

    GtkWidget *activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(activity), "activity");
    gtk_container_add(GTK_CONTAINER(window), activity);

    GtkWidget *activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), window_size_x, window_size_y);
    gtk_container_add(GTK_CONTAINER(activity), activity_block);
    
    start_screen(&activity_block);
    gtk_widget_show_all(window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}
