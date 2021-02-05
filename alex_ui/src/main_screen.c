#include "Chat.h"

void main_screen() {
  
    gtk_widget_destroy(GTK_WIDGET(main_data.activity_block));
    
    gtk_css_provider_load_from_path(main_data.styles, "resource/styles/main_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    
    main_data.main_box.all_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.all_main_box), "main_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.all_main_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.all_main_box, 0, 0);

    // Gtk fixed
    main_data.main_box.main_fixed = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.main_fixed), 300, 100);
    gtk_container_add(GTK_CONTAINER(main_data.main_box.all_main_box), main_data.main_box.main_fixed);
    
    // Chat bar
    main_data.main_box.chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.chat_bar, 0, 0);

        // Up box
        GtkWidget *up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(up_box), "up_box");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar), up_box, FALSE, FALSE, 0);

            // User photo
            GtkWidget *user_settings_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(user_settings_button), "user_settings_button");
            gtk_box_pack_start(GTK_BOX(up_box), user_settings_button, FALSE, FALSE, 0);

            g_signal_connect(G_OBJECT(user_settings_button), "button_press_event", G_CALLBACK(show_user_settings), NULL);

            GtkWidget *user_settings_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(user_settings_button_box), "user_settings_button_box");
            gtk_container_add(GTK_CONTAINER(user_settings_button), user_settings_button_box);

            GtkWidget *user_avatar = gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_WIDGET(user_avatar), 80, 80);
        
            char *path = strdup("resource/images/anonymous.png");
        
            g_signal_connect(G_OBJECT(user_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

            GtkWidget *user_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(user_photo), "user_photo");
            gtk_container_add(GTK_CONTAINER(user_photo), user_avatar);
            gtk_box_pack_start(GTK_BOX(user_settings_button_box), user_photo, FALSE, FALSE, 0);

            // User name
            GtkWidget *user_name_label = gtk_label_new("%username%");
            gtk_widget_set_halign(GTK_WIDGET(user_name_label), GTK_ALIGN_START);
            gtk_widget_set_name(GTK_WIDGET(user_name_label), "user_name_label");
            gtk_box_pack_start(GTK_BOX(up_box), user_name_label, FALSE, FALSE, 0);

            // Add new chat button
            GtkWidget *add_new_chat_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(add_new_chat_button), "add_new_chat_button");
            gtk_widget_set_halign(GTK_WIDGET(add_new_chat_button), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(add_new_chat_button), GTK_ALIGN_CENTER);
            gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), add_new_chat_button, 250, 10);

            g_signal_connect(G_OBJECT(add_new_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(add_new_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(add_new_chat_button), "button_press_event", G_CALLBACK(show_add_new_chat), NULL);

            GtkWidget *add_new_chat_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
            gtk_widget_set_name(GTK_WIDGET(add_new_chat_button_box), "add_new_chat_button_box");
            gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_button_box), 20, 20);
            gtk_container_add(GTK_CONTAINER(add_new_chat_button), add_new_chat_button_box);

            // Exit button
            GtkWidget *exit_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
            gtk_widget_set_halign(GTK_WIDGET(exit_button), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(exit_button), GTK_ALIGN_CENTER);
            gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), exit_button, 280, 10);

            g_signal_connect(G_OBJECT(exit_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(exit_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(exit_button), "button_press_event", G_CALLBACK(logout), NULL);

            GtkWidget *exit_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(exit_button_box), "exit_button_box");
            gtk_widget_set_size_request(GTK_WIDGET(exit_button_box), 19, 19);
            gtk_container_add(GTK_CONTAINER(exit_button), exit_button_box);
        
        // Chat list
        load_chat_list();

    // Chat box
    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.right_chat_box, 310, 0);

    if(main_data.main_box.search_chat_id == -1) {
        GtkWidget *right_mid_box = gtk_label_new("Whom you want to write?");
        gtk_widget_set_name(GTK_WIDGET(right_mid_box), "right_mid_box");
        gtk_widget_set_size_request(GTK_WIDGET(right_mid_box), 240, 40);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), right_mid_box, TRUE, FALSE, 0);
    }
    
    gtk_widget_show_all(main_data.activity_block);
}
