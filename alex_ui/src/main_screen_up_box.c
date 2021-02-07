#include "Chat.h"

void main_screen_up_box() {
    main_data.main_box.up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.up_box), "up_box");
    gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar), main_data.main_box.up_box, FALSE, FALSE, 0);

        // User photo
        GtkWidget *user_settings_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(user_settings_button), "user_settings_button");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.up_box), user_settings_button, FALSE, FALSE, 0);

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
        main_data.main_box.user_name_label = gtk_label_new(user_data.name);
        gtk_label_set_selectable(GTK_LABEL(main_data.main_box.user_name_label), TRUE);
        gtk_label_set_line_wrap(GTK_LABEL(main_data.main_box.user_name_label), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(main_data.main_box.user_name_label), PANGO_WRAP_WORD_CHAR);
        gtk_label_set_max_width_chars(GTK_LABEL(main_data.main_box.user_name_label), 18);
        gtk_widget_set_halign(GTK_WIDGET(main_data.main_box.user_name_label), GTK_ALIGN_START);
        gtk_widget_set_name(GTK_WIDGET(main_data.main_box.user_name_label), "user_name_label");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.up_box), main_data.main_box.user_name_label, FALSE, FALSE, 0);

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
}
