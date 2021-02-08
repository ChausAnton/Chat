#include "Chat.h"

void show_rename_chat(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
    
    main_data.main_box.rename_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.rename_chat_event_box), "user_settings_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.rename_chat_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.rename_chat_event_box), "button_press_event", G_CALLBACK(unpress_chat_settings), NULL);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.rename_chat_event_box, 0, 0);

    GtkWidget *position_user_settings = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.rename_chat_event_box), position_user_settings);

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

    GtkWidget *user_settings_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_settings_avatar), 100, 100);
    char *path = strdup(user_data.chat_array[main_data.main_box.search_chat_id].image_path);
    g_signal_connect(G_OBJECT(user_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), path);

    GtkWidget *user_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_settings_photo), "user_settings_photo");
    gtk_container_add(GTK_CONTAINER(user_settings_photo), user_settings_avatar);
    gtk_box_pack_start(GTK_BOX(scrollable_box), user_settings_photo, FALSE, FALSE, 0);

    GtkEntryBuffer *nickname = gtk_entry_buffer_new(user_data.chat_array[main_data.main_box.search_chat_id].chat_name, -1);

    GtkWidget *user_nickname = gtk_entry_new_with_buffer(nickname);
    gtk_widget_set_name(GTK_WIDGET(user_nickname), "user_nickname");
    gtk_entry_set_max_length(GTK_ENTRY(user_nickname), 20);
    gtk_widget_set_halign(GTK_WIDGET(user_nickname), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(user_nickname), GTK_ALIGN_CENTER);
    /*char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(sign_in_data[0])));
    printf("login: %s\n", name);*/
    gtk_entry_set_placeholder_text (GTK_ENTRY(user_nickname), "Lol");
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

    g_signal_connect(G_OBJECT(save_event_box), "button_press_event", G_CALLBACK(save_rename_chat_changes), scrollable_box);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.rename_chat_event_box));
}

void save_rename_chat_changes(GtkWidget *widget, GdkEventButton *event, gpointer *data) {
    if(widget&&event){}
    GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget *)data));
    user_data.chat_array[main_data.main_box.search_chat_id].chat_name = strdup((char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(parent->next->data))));
    gtk_label_set_text(GTK_LABEL(user_data.chat_array[main_data.main_box.search_chat_id].chat_label_name), user_data.chat_array[main_data.main_box.search_chat_id].chat_name);
    gtk_label_set_text(GTK_LABEL(main_data.main_box.chat_box_name_label), user_data.chat_array[main_data.main_box.search_chat_id].chat_name);
    
    gtk_widget_unset_state_flags(GTK_WIDGET(main_data.main_box.chat_settings_button), GTK_STATE_FLAG_ACTIVE);
    gtk_widget_destroy(main_data.main_box.chat_settings_event_box);
    gtk_widget_destroy(main_data.main_box.rename_chat_event_box);
}
