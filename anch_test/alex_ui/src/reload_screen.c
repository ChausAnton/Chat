#include "Chat.h"

void reload_screen() {

    gtk_widget_destroy(GTK_WIDGET(main_data.activity_block));

    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);

    gtk_css_provider_load_from_path(main_data.styles, main_data.reload_box.css, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    
    main_data.reload_box.all_reload_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.reload_box.all_reload_box), "reload_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.reload_box.all_reload_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.reload_box.all_reload_box, 0, 0);

    GtkWidget *exit_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    gtk_widget_set_halign(GTK_WIDGET(exit_button), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(exit_button), GTK_ALIGN_START);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), exit_button, 10, 10);

    g_signal_connect(G_OBJECT(exit_button), "button_press_event", G_CALLBACK(logout), NULL);

    GtkWidget *exit_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(exit_button_box), "exit_button_box");
    gtk_widget_set_size_request(GTK_WIDGET(exit_button_box), 25, 25);
    gtk_container_add(GTK_CONTAINER(exit_button), exit_button_box);

    GtkWidget *server_lost_label = gtk_label_new("Ooooops...");
    gtk_widget_set_name(GTK_WIDGET(server_lost_label), "server_lost_label");
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), server_lost_label, 670, 280);

    GtkWidget *server_lost_label1 = gtk_label_new("Something went wrong with server connection :(");
    gtk_widget_set_name(GTK_WIDGET(server_lost_label1), "server_lost_label");
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), server_lost_label1, 530, 300);

    GtkWidget *server_lost_label2 = gtk_label_new("Go drink some coffee while we fixing this issue :)");
    gtk_widget_set_name(GTK_WIDGET(server_lost_label2), "server_lost_label");
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), server_lost_label2, 530, 630);

    GError *error = NULL;
    GdkPixbufAnimation *gif = gdk_pixbuf_animation_new_from_file("resource/images/coffe_cat.gif", &error);

    GtkWidget *cat_gif = gtk_image_new_from_animation (gif);
    gtk_widget_set_halign(GTK_WIDGET(cat_gif), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(cat_gif), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_data.reload_box.all_reload_box), cat_gif, TRUE, TRUE, 0);

    gtk_widget_show_all(main_data.reload_box.all_reload_box);
    gtk_widget_show_all(main_data.activity_block);
}
