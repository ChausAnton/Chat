#include "Chat.h"

void load_chat_list() {
    main_data.main_box.chat_bar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.chat_bar_scroll), 0, 0);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar), main_data.main_box.chat_bar_scroll, TRUE, TRUE, 0);   

    main_data.main_box.chat_bar_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_bar_for_scroll), "chat_bar_for_scroll");
    gtk_container_add(GTK_CONTAINER(main_data.main_box.chat_bar_scroll), main_data.main_box.chat_bar_for_scroll);

    for(int i = 0; i < user_data.amount_of_chat; i++) {
        GtkWidget *chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_button), "chat_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar_for_scroll), chat_button, FALSE, FALSE, 0);

        GtkWidget *chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_box), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(chat_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(chat_button), chat_box);
        
        GtkWidget *left_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(left_chat_avatar), 40, 40);
        char *path = strdup(user_data.chat_array[i].image_path);

        g_signal_connect(G_OBJECT(left_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

        GtkWidget* photo_chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(photo_chat), "left_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(photo_chat), left_chat_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(photo_chat), 50, 30);
        gtk_box_pack_start(GTK_BOX(chat_box), photo_chat, FALSE, FALSE, 0);

        GtkWidget* name_chat = gtk_label_new(user_data.chat_array[i].chat_name);
        gtk_widget_set_name(GTK_WIDGET(name_chat), "chat_name");
        gtk_box_pack_start(GTK_BOX(chat_box), name_chat, FALSE, FALSE, 0);

        GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[i].chat_id));
        gtk_box_pack_start(GTK_BOX(chat_box), chat_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

        g_signal_connect(G_OBJECT(chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "button_press_event", G_CALLBACK(chat_click), NULL);
    }
}
