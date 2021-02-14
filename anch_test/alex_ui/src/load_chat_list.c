#include "Chat.h"

void load_chat_list() {
    main_data.main_box.chat_bar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.chat_bar_scroll), 0, 0);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar), main_data.main_box.chat_bar_scroll, TRUE, TRUE, 0);   

    main_data.main_box.chat_bar_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_bar_for_scroll), "chat_bar_for_scroll");
    gtk_container_add(GTK_CONTAINER(main_data.main_box.chat_bar_scroll), main_data.main_box.chat_bar_for_scroll);
    int current = -1;
    for(int i = 0; i < user_data.amount_of_chat; i++) {
        user_data.chat_array[i].chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[i].chat_button), "chat_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(user_data.chat_array[i].chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar_for_scroll), user_data.chat_array[i].chat_button, FALSE, FALSE, 0);

        user_data.chat_array[i].chat_list_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[i].chat_list_box), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[i].chat_list_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[i].chat_button), user_data.chat_array[i].chat_list_box);

        user_data.chat_array[i].chat_list_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[i].chat_list_avatar), 40, 40);
        char *path = strdup(user_data.chat_array[i].image_path);
        user_data.chat_array[i].temp_source_path = user_data.chat_array[i].image_path;

        g_signal_connect(G_OBJECT(user_data.chat_array[i].chat_list_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

        user_data.chat_array[i].chat_list_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[i].chat_list_photo), "left_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[i].chat_list_photo), user_data.chat_array[i].chat_list_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[i].chat_list_photo), 50, 30);
        gtk_box_pack_start(GTK_BOX(user_data.chat_array[i].chat_list_box), user_data.chat_array[i].chat_list_photo, FALSE, FALSE, 0);

        user_data.chat_array[i].chat_label_name = gtk_label_new(user_data.chat_array[i].chat_name);
        gtk_label_set_line_wrap(GTK_LABEL(user_data.chat_array[i].chat_label_name), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(user_data.chat_array[i].chat_label_name), PANGO_WRAP_WORD_CHAR);
        gtk_label_set_max_width_chars(GTK_LABEL(user_data.chat_array[i].chat_label_name), 18);
        gtk_label_set_selectable(GTK_LABEL(user_data.chat_array[i].chat_label_name), TRUE);
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[i].chat_label_name), "chat_name");
        gtk_box_pack_start(GTK_BOX(user_data.chat_array[i].chat_list_box), user_data.chat_array[i].chat_label_name, FALSE, FALSE, 0);

        GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[i].chat_id));
        gtk_box_pack_start(GTK_BOX(user_data.chat_array[i].chat_list_box), chat_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

        g_signal_connect(G_OBJECT(user_data.chat_array[i].chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
        g_signal_connect(G_OBJECT(user_data.chat_array[i].chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);
        
        g_signal_connect(G_OBJECT(user_data.chat_array[i].chat_button), "button_press_event", G_CALLBACK(chat_click), (gpointer)&current);        
    }
}
