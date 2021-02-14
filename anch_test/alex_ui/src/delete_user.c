#include "Chat.h"

void show_delete_user(GtkWidget *widget) {

    main_data.main_box.is_first_search_destroy = false;

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    main_data.main_box.add_new_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.add_new_chat_event_box), "add_new_chat_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.add_new_chat_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.add_new_chat_event_box), "button_press_event", G_CALLBACK(unpress_chat_settings), NULL);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.add_new_chat_event_box, 0, 0);

    GtkWidget *position_add_new_chat = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.add_new_chat_event_box), position_add_new_chat);

    GtkWidget *clickable_add_new_chat = gtk_event_box_new();
    //gtk_widget_set_name(GTK_WIDGET(clickable_add_new_chat), "clickable_add_new_chat");
    gtk_widget_set_halign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_add_new_chat), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
  
    gtk_fixed_put(GTK_FIXED(position_add_new_chat), clickable_add_new_chat, 640, 120);

    GtkWidget *add_new_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(add_new_chat_box), "delete_chat_box");
    gtk_container_add(GTK_CONTAINER(clickable_add_new_chat), add_new_chat_box);

    GtkWidget *horizontal_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(horizontal_box), "horizontal_box");
    gtk_widget_set_size_request(GTK_WIDGET(horizontal_box), 400, 20);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), horizontal_box, FALSE, FALSE, 0);

    // Scroll
    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 520);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *add_chats_scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(add_chats_scrollable_box), "add_chats_scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), add_chats_scrollable_box);

    for(int i = 0; i < user_data.chat_array[main_data.main_box.search_chat_index].count_users; i++) {

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

        g_signal_connect(G_OBJECT(add_new_chat_avatar), "draw", G_CALLBACK(draw_user_avatar), "resource/images/user_icon.png");

        GtkWidget *add_new_chat_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(add_new_chat_photo), "add_new_chat_photo");
        gtk_container_add(GTK_CONTAINER(add_new_chat_photo), add_new_chat_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_photo), 50, 30);
        gtk_box_pack_start(GTK_BOX(search_chat_box), add_new_chat_photo, FALSE, FALSE, 0);

        GtkWidget* user_name_in_search = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].name);
        gtk_widget_set_name(GTK_WIDGET(user_name_in_search), "user_name_in_search");
        gtk_box_pack_start(GTK_BOX(search_chat_box), user_name_in_search, FALSE, FALSE, 0);

        GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].user_id));
        gtk_box_pack_start(GTK_BOX(search_chat_box), chat_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

        g_signal_connect(G_OBJECT(search_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
        g_signal_connect(G_OBJECT(search_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);
        
        g_signal_connect(G_OBJECT(search_chat_button), "button_press_event", G_CALLBACK(search_user_click), NULL);
    }
    
    GtkWidget *delete_user_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(delete_user_event_box), "new_chat_event_box");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(delete_user_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), delete_user_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_user_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(delete_user_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *delete_user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(delete_user_box), "new_chat_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(delete_user_box), 280, 70);
    gtk_container_add(GTK_CONTAINER(delete_user_event_box), delete_user_box);

    GtkWidget *delete_user_box_label = gtk_label_new("Delete user");
    gtk_widget_set_name(GTK_WIDGET(delete_user_box_label), "delete_user_box_label");
    gtk_widget_set_halign(GTK_WIDGET(delete_user_box_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(delete_user_box_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(delete_user_box), delete_user_box_label, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_user_event_box), "button_press_event", G_CALLBACK(delete_user), NULL);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.add_new_chat_event_box));
}

void delete_user() {
    int usr_amnt = user_data.chat_array[main_data.main_box.search_chat_index].count_users; // amount of users in current chat
    for(int i = 0; i < 100; i++){
        if(new_chat_users_id[i] != -1) {
            usr_amnt--;
        }
    }
    
    user_data.chat_array[main_data.main_box.search_chat_index].count_users = usr_amnt;

    for(int i = 0; i < 100; i++) new_chat_users_id[i] = -1;

    gtk_widget_destroy(main_data.main_box.add_new_chat_event_box);
    gtk_widget_destroy(main_data.main_box.chat_settings_event_box);
    
    gtk_widget_show_all(main_data.main_box.chat_bar);
}
