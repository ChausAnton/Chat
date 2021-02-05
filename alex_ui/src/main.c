#include "Chat.h"


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    main_data.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_data.window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(main_data.window), FALSE);
    gtk_window_set_position(GTK_WINDOW(main_data.window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(main_data.window), WINDOW_SIZE_X, WINDOW_SIZE_Y);

    main_data.activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.activity), "activity");
    gtk_container_add(GTK_CONTAINER(main_data.window), main_data.activity);
    
    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    //g_signal_connect(window, "activate-default", G_CALLBACK(start_screen), (void *)activity_block);
    main_data.styles = gtk_css_provider_new();
    //gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    for(int i =0; i < 100; i++){
        new_chat_users_id[i] = -1;
    }
    start_screen();
     
    gtk_widget_show_all(main_data.window);
    g_signal_connect(main_data.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}
