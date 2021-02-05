#include "Chat.h"

void show_add_new_chat(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    GtkWidget *add_new_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(add_new_chat_event_box), "add_new_chat_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(add_new_chat_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), add_new_chat_event_box, 0, 0);

    GtkWidget *position_add_new_chat = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(add_new_chat_event_box), position_add_new_chat);

    GtkWidget *clickable_add_new_chat = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(clickable_add_new_chat), "clickable_add_new_chat");
    gtk_widget_set_halign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_add_new_chat), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
  
    gtk_fixed_put(GTK_FIXED(position_add_new_chat), clickable_add_new_chat, 630, 140);

    GtkWidget *add_new_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(add_new_chat_box), "add_new_chat_box");
    gtk_container_add(GTK_CONTAINER(clickable_add_new_chat), add_new_chat_box);

    GtkWidget *search_users = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_users), "search_users");
    gtk_entry_set_max_length(GTK_ENTRY(search_users), 30);
    gtk_entry_set_placeholder_text (GTK_ENTRY(search_users), "Search");
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), search_users, FALSE, FALSE, 0);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 520);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *add_chats_scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(add_chats_scrollable_box), "add_chats_scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), add_chats_scrollable_box);

    for(int i = 0; i < 15; i++) {
        GtkWidget *search_chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(search_chat_button), "user_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(search_chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(add_chats_scrollable_box), search_chat_button, FALSE, FALSE, 0);

        GtkWidget *search_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(search_chat_box), "user_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(search_chat_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(search_chat_button), search_chat_box);
        
        GtkWidget *add_new_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_avatar), 80, 80);
        char *path = strdup("resource/images/sh.jpg");

        g_signal_connect(G_OBJECT(add_new_chat_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

        GtkWidget *add_new_chat_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(add_new_chat_photo), "add_new_chat_photo");
        gtk_container_add(GTK_CONTAINER(add_new_chat_photo), add_new_chat_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_photo), 50, 30);
        gtk_box_pack_start(GTK_BOX(search_chat_box), add_new_chat_photo, FALSE, FALSE, 0);

        GtkWidget* user_name_in_search = gtk_label_new("Shrek))0)");
        gtk_widget_set_name(GTK_WIDGET(user_name_in_search), "user_name_in_search");
        gtk_box_pack_start(GTK_BOX(search_chat_box), user_name_in_search, FALSE, FALSE, 0);

        GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[i].chat_id));
        gtk_box_pack_start(GTK_BOX(search_chat_box), chat_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

        g_signal_connect(G_OBJECT(search_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
        g_signal_connect(G_OBJECT(search_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);
        
        g_signal_connect(G_OBJECT(search_chat_button), "button_press_event", G_CALLBACK(search_user_click), NULL);
    }
    
    GtkWidget *new_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(new_chat_event_box), "new_chat_event_box");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(new_chat_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), new_chat_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(new_chat_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(new_chat_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *new_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(new_chat_box), "new_chat_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(new_chat_box), 280, 70);
    gtk_container_add(GTK_CONTAINER(new_chat_event_box), new_chat_box);

    GtkWidget *new_chat_box_label = gtk_label_new("New chat");
    gtk_widget_set_name(GTK_WIDGET(new_chat_box_label), "new_chat_box_label");
    gtk_widget_set_halign(GTK_WIDGET(new_chat_box_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(new_chat_box_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(new_chat_box), new_chat_box_label, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(new_chat_event_box), "button_press_event", G_CALLBACK(create_new_chat), NULL);

    gtk_widget_show_all(GTK_WIDGET(add_new_chat_event_box));
}
