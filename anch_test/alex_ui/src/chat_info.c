#include "../inc/Chat.h"

void show_chat_info(GtkWidget *widget) {
    new_user = true;
    while(new_user == true) {};
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    GtkWidget *chat_info_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(chat_info_event_box), "chat_info_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(chat_info_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(chat_info_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), chat_info_event_box, 0, 0);

    GtkWidget *position_chat_info = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(chat_info_event_box), position_chat_info);

    GtkWidget *clickable_chat_info = gtk_event_box_new();
    //gtk_widget_set_name(GTK_WIDGET(clickable_chat_info), "clickable_chat_info");
    gtk_widget_set_halign(GTK_WIDGET(clickable_chat_info), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_chat_info), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_chat_info), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
  
    gtk_fixed_put(GTK_FIXED(position_chat_info), clickable_chat_info, 640, 100);

    GtkWidget *chat_info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_info_box), "chat_info_box");
    gtk_container_add(GTK_CONTAINER(clickable_chat_info), chat_info_box);

    GtkWidget *chat_info_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(chat_info_avatar), 100, 100);
    char *path = strdup(user_data.chat_array[main_data.main_box.search_chat_index].image_path);
    g_signal_connect(G_OBJECT(chat_info_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), path); 
    
    GtkWidget *chat_info_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_info_photo), "chat_info_photo");
    gtk_container_add(GTK_CONTAINER(chat_info_photo), chat_info_avatar);
    gtk_box_pack_start(GTK_BOX(chat_info_box), chat_info_photo, FALSE, FALSE, 0);

    GtkWidget *chat_name_label = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].chat_name);
    gtk_label_set_selectable(GTK_LABEL(chat_name_label), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    gtk_widget_set_name(GTK_WIDGET(chat_name_label), "chat_name_label");
    gtk_box_pack_start(GTK_BOX(chat_info_box), chat_name_label, FALSE, FALSE, 0);

    char *usr_amnt = mx_strjoin(int_to_str(user_data.chat_array[main_data.main_box.search_chat_index].count_users), " users");

    GtkWidget *amnt_of_users_in_chat_label = gtk_label_new(usr_amnt);
    gtk_widget_set_halign(GTK_WIDGET(amnt_of_users_in_chat_label), GTK_ALIGN_START);
    gtk_widget_set_name(GTK_WIDGET(amnt_of_users_in_chat_label), "amnt_of_users_in_chat_label");
    gtk_box_pack_start(GTK_BOX(chat_info_box), amnt_of_users_in_chat_label, FALSE, FALSE, 0);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 520);
    gtk_box_pack_start(GTK_BOX(chat_info_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *chat_info_scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_info_scrollable_box), "chat_info_scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), chat_info_scrollable_box);

    mx_printerr("!!!!!!!!!\n");
    mx_printerr(mx_itoa(user_data.chat_array[main_data.main_box.search_chat_index].count_users));
    mx_printerr("!!!!!!!!!\n");
    for(int i = 0; i < user_data.chat_array[main_data.main_box.search_chat_index].count_users; i++) {

        GtkWidget *search_chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(search_chat_button), "user_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(search_chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(chat_info_scrollable_box), search_chat_button, FALSE, FALSE, 0);

        GtkWidget *search_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(search_chat_box), "user_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(search_chat_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(search_chat_button), search_chat_box);
        
        GtkWidget *chat_info_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(chat_info_avatar), 80, 80);
        g_signal_connect(G_OBJECT(chat_info_avatar), "draw", G_CALLBACK(draw_user_avatar), user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].image_path);
        //mx_printerr(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].image_path);
        //mx_printerr("\n");

        GtkWidget *chat_info_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_info_photo), "chat_info_photo");
        gtk_container_add(GTK_CONTAINER(chat_info_photo), chat_info_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(chat_info_photo), 50, 30);
        gtk_box_pack_start(GTK_BOX(search_chat_box), chat_info_photo, FALSE, FALSE, 0);

        GtkWidget* user_name_in_search = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].name);
        gtk_widget_set_name(GTK_WIDGET(user_name_in_search), "user_name_in_search");
        gtk_box_pack_start(GTK_BOX(search_chat_box), user_name_in_search, FALSE, FALSE, 0);

        GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].user_id));
        gtk_box_pack_start(GTK_BOX(search_chat_box), chat_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

        g_signal_connect(G_OBJECT(search_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
        g_signal_connect(G_OBJECT(search_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

        //g_signal_connect(G_OBJECT(search_chat_button), "button_press_event", G_CALLBACK(search_user_click), NULL);
    }

    gtk_widget_show_all(GTK_WIDGET(chat_info_event_box));
    gtk_widget_show_all(GTK_WIDGET(main_data.activity_block));
}
