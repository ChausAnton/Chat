#include "Chat.h"

void show_chat_settings(GtkWidget *widget) {
    
    static int number1 = EDIT_CHAT;
    static int number2 = ADD_USER;
    static int number3 = DELETE_USER;
    static int number4 = DELETE_CHAT;
    //static int number5 = CHANGE_CHAT_IMAGE;

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
    
    main_data.main_box.chat_settings_event_box = gtk_event_box_new();
    //gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_settings_event_box), "chat_settings_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.chat_settings_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.chat_settings_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.chat_settings_event_box, 0, 0);

    GtkWidget *position_chat_settings = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.chat_settings_event_box), position_chat_settings);

    GtkWidget *clickable_chat_settings = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable_chat_settings), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_chat_settings), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_chat_settings), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(position_chat_settings), clickable_chat_settings, 1155, 70);

    GtkWidget *chat_settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(chat_settings_box), "chat_settings_box");
    gtk_container_add(GTK_CONTAINER(clickable_chat_settings), chat_settings_box);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 230, 152);
    gtk_box_pack_start(GTK_BOX(chat_settings_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(scrollable_box), "scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), scrollable_box);

    // Edit chat
    GtkWidget *edit_chat_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(edit_chat_clickable), "edit_chat");
    gtk_box_pack_start(GTK_BOX(scrollable_box), edit_chat_clickable, FALSE, FALSE, 0);
    
    g_signal_connect(G_OBJECT(edit_chat_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(edit_chat_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

    GtkWidget *edit_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(edit_chat_box), "edit_chat_box");
    gtk_container_add(GTK_CONTAINER(edit_chat_clickable), edit_chat_box);

    GtkWidget *edit_chat_icon = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_chat_icon), "edit_chat_icon");
    gtk_widget_set_size_request(GTK_WIDGET(edit_chat_icon), 25, 25);
    gtk_box_pack_start(GTK_BOX(edit_chat_box), edit_chat_icon, FALSE, FALSE, 0);

    GtkWidget *edit_chat = gtk_label_new("Edit chat");
    gtk_widget_set_name(GTK_WIDGET(edit_chat), "chat_settings_labels");
    gtk_widget_set_halign(GTK_WIDGET(edit_chat), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(edit_chat_box), edit_chat, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(edit_chat_clickable), "button_press_event", G_CALLBACK(chat_settings_click), (gpointer) &number1);

    // Add user
    GtkWidget *add_user_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(add_user_clickable), "add_user");
    gtk_box_pack_start(GTK_BOX(scrollable_box), add_user_clickable, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(add_user_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(add_user_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

    GtkWidget *add_user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(add_user_box), "add_user_box");
    gtk_container_add(GTK_CONTAINER(add_user_clickable), add_user_box);

    GtkWidget *add_user_icon = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(add_user_icon), "add_user_icon");
    gtk_widget_set_size_request(GTK_WIDGET(add_user_icon), 25, 25);
    gtk_box_pack_start(GTK_BOX(add_user_box), add_user_icon, FALSE, FALSE, 0);

    GtkWidget *add_user = gtk_label_new("Add user");
    gtk_widget_set_name(GTK_WIDGET(add_user), "chat_settings_labels");
    gtk_widget_set_halign(GTK_WIDGET(add_user), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(add_user_box), add_user, FALSE, FALSE, 0);
    
    g_signal_connect(G_OBJECT(add_user_clickable), "button_press_event", G_CALLBACK(chat_settings_click), (gpointer) &number2);
  
    // Delete user
    GtkWidget *delete_user_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(delete_user_clickable), "delete_user");
    gtk_box_pack_start(GTK_BOX(scrollable_box), delete_user_clickable, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_user_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(delete_user_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

    GtkWidget *delete_user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(delete_user_box), "delete_user_box");
    gtk_container_add(GTK_CONTAINER(delete_user_clickable), delete_user_box);

    GtkWidget *delete_user_icon = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(delete_user_icon), "delete_user_icon");
    gtk_widget_set_size_request(GTK_WIDGET(delete_user_icon), 25, 25);
    gtk_box_pack_start(GTK_BOX(delete_user_box), delete_user_icon, FALSE, FALSE, 0);

    GtkWidget *delete_user = gtk_label_new("Delete user");
    gtk_widget_set_name(GTK_WIDGET(delete_user), "chat_settings_labels");
    gtk_widget_set_halign(GTK_WIDGET(delete_user), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(delete_user_box), delete_user, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_user_clickable), "button_press_event", G_CALLBACK(chat_settings_click), (gpointer) &number3);

    // Delete chat
    GtkWidget *delete_chat_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(delete_chat_clickable), "delete_chat");
    gtk_box_pack_start(GTK_BOX(scrollable_box), delete_chat_clickable, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_chat_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(delete_chat_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

    GtkWidget *delete_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(delete_chat_box), "delete_chat_box");
    gtk_container_add(GTK_CONTAINER(delete_chat_clickable), delete_chat_box);

    GtkWidget *delete_chat_icon = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(delete_chat_icon), "delete_chat_icon");
    gtk_widget_set_size_request(GTK_WIDGET(delete_chat_icon), 25, 25);
    gtk_box_pack_start(GTK_BOX(delete_chat_box), delete_chat_icon, FALSE, FALSE, 0);

    GtkWidget *delete_chat = gtk_label_new("Delete chat");
    gtk_widget_set_name(GTK_WIDGET(delete_chat), "chat_settings_labels");
    gtk_widget_set_halign(GTK_WIDGET(delete_chat), GTK_ALIGN_START);        
    gtk_box_pack_start(GTK_BOX(delete_chat_box), delete_chat, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_chat_clickable), "button_press_event", G_CALLBACK(chat_settings_click), (gpointer) &number4);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.chat_settings_event_box));
}
