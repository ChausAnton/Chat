#include "Chat.h"

void show_change_chat_image(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    main_data.main_box.change_chat_image_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.change_chat_image_event_box), "user_settings_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.change_chat_image_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.change_chat_image_event_box), "button_press_event", G_CALLBACK(unpress_chat_settings), NULL);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.change_chat_image_event_box, 0, 0);

    GtkWidget *position_user_settings = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.change_chat_image_event_box), position_user_settings);

    GtkWidget *clickable_user_settings = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable_user_settings), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_user_settings), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_user_settings), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

    gtk_fixed_put(GTK_FIXED(position_user_settings), clickable_user_settings, 680, 320);

    GtkWidget *user_settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(user_settings_box), "user_settings_box");
    gtk_container_add(GTK_CONTAINER(clickable_user_settings), user_settings_box);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 200);
    gtk_box_pack_start(GTK_BOX(user_settings_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(scrollable_box), "scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), scrollable_box);

    //Chat settings photo
    user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box), "user_settings_photo_event_box");
    gtk_box_pack_start(GTK_BOX(scrollable_box), user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box, FALSE, FALSE, 0);

    user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar), 100, 100);
    char *path = strdup(user_data.chat_array[main_data.main_box.search_chat_id].image_path);
    g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), path);

    user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo), "user_settings_photo");
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo), user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar);
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box), user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo);

    g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box), "button_press_event", G_CALLBACK(change_photo), scrollable_box);

    //Nickname
    GtkWidget *user_nickname = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_id].chat_name);
    gtk_widget_set_name(GTK_WIDGET(user_nickname), "user_nickname_in_change_image");
    gtk_widget_set_halign(GTK_WIDGET(user_nickname), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(user_nickname), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(scrollable_box), user_nickname, FALSE, FALSE, 0);

    //Save button
    GtkWidget *save_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(save_event_box), "save_event_box");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(save_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(scrollable_box), save_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(save_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(save_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *save_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(save_box), "save_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(save_box), 280, 70);
    gtk_container_add(GTK_CONTAINER(save_event_box), save_box);

    GtkWidget *save_box_label = gtk_label_new("Save changes");
    gtk_widget_set_name(GTK_WIDGET(save_box_label), "save_box_label");
    gtk_widget_set_halign(GTK_WIDGET(save_box_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(save_box_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(save_box), save_box_label, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(save_event_box), "button_press_event", G_CALLBACK(save_change_chat_image_changes), scrollable_box);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.change_chat_image_event_box));
}

void save_change_chat_image_changes(GtkWidget *widget) {
    if(widget){}
    user_data.chat_array[main_data.main_box.search_chat_id].image_path = user_data.chat_array[main_data.main_box.search_chat_id].temp_source_path;

    gtk_widget_destroy(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo);
    gtk_widget_destroy(main_data.main_box.chat_bar_scroll);

    user_data.chat_array[main_data.main_box.search_chat_id].chat_box_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_avatar), 40, 40);
    g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_avatar), "draw", G_CALLBACK(draw_chat_avatar), user_data.chat_array[main_data.main_box.search_chat_id].image_path);
    
    user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo), "top_chat_photo");
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo), user_data.chat_array[main_data.main_box.search_chat_id].chat_box_avatar);
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo_event_box), user_data.chat_array[main_data.main_box.search_chat_id].chat_box_photo);

    load_chat_list();

    gtk_widget_hide(main_data.main_box.right_chat_box);
    gtk_widget_show_all(main_data.main_box.right_chat_box);
    gtk_widget_hide(main_data.main_box.chat_bar_scroll);
    gtk_widget_show_all(main_data.main_box.chat_bar_scroll);
    gtk_widget_unset_state_flags(GTK_WIDGET(main_data.main_box.chat_settings_button), GTK_STATE_FLAG_ACTIVE);
    gtk_widget_destroy(main_data.main_box.chat_settings_event_box);
    gtk_widget_destroy(main_data.main_box.change_chat_image_event_box);
}
