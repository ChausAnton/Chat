#include "Chat.h"

void delete_chat() {

    user_data.chat_array[main_data.main_box.search_chat_id].chat_id  = -1;

    for(int i = main_data.main_box.search_chat_id; user_data.chat_array[user_data.amount_of_chat - 1].chat_id != -1; ++i) { 
        t_chat_list temp = user_data.chat_array[i];
        user_data.chat_array[i] = user_data.chat_array[i + 1];
        user_data.chat_array[i + 1] = temp;
    }

    user_data.amount_of_chat--;

    gtk_widget_destroy(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_button));
    gtk_widget_destroy(GTK_WIDGET(main_data.main_box.delete_chat_event_box));
    gtk_widget_destroy(main_data.main_box.chat_settings_event_box);
    gtk_widget_destroy(main_data.main_box.right_chat_box);
    gtk_widget_destroy(main_data.main_box.chat_bar_scroll);

    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.right_chat_box, 310, 0);

    GtkWidget *right_mid_box = gtk_label_new("Whom you want to write?");
    gtk_widget_set_name(GTK_WIDGET(right_mid_box), "right_mid_box");
    gtk_widget_set_size_request(GTK_WIDGET(right_mid_box), 240, 40);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), right_mid_box, TRUE, FALSE, 0);

    gtk_widget_show_all(main_data.main_box.right_chat_box);

    load_chat_list();
    gtk_widget_hide(main_data.main_box.chat_bar_scroll);
    gtk_widget_show_all(main_data.main_box.chat_bar_scroll);
}

void show_delete_chat(GtkWidget *widget) {

    main_data.main_box.delete_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.delete_chat_event_box), "delete_chat_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.delete_chat_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.delete_chat_event_box), "button_press_event", G_CALLBACK(gtk_widget_show), widget);
    //g_signal_connect(G_OBJECT(delete_chat_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.delete_chat_event_box, 0, 0);

    GtkWidget *position_delete_chat = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.delete_chat_event_box), position_delete_chat);

    GtkWidget *clickable_delete_chat = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable_delete_chat), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable_delete_chat), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(clickable_delete_chat), 300, 130);
    gtk_fixed_put(GTK_FIXED(position_delete_chat), clickable_delete_chat, 580, 300);
    g_signal_connect(G_OBJECT(clickable_delete_chat), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

    GtkWidget *delete_chat_func_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(delete_chat_func_box), "delete_chat_func_box");
    gtk_container_add(GTK_CONTAINER(clickable_delete_chat), delete_chat_func_box);

    GtkWidget *delete_chat_label = gtk_label_new("Are you sure you want to delete this chat?");
    gtk_widget_set_name(GTK_WIDGET(delete_chat_label), "delete_chat_label");
    gtk_box_pack_start(GTK_BOX(delete_chat_func_box), delete_chat_label, FALSE, FALSE, 0);

    GtkWidget *delete_chat_box_for_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_name(GTK_WIDGET(delete_chat_box_for_buttons), "delete_chat_box_for_buttons");
    gtk_box_pack_start(GTK_BOX(delete_chat_func_box), delete_chat_box_for_buttons, FALSE, FALSE, 10);

    GtkWidget *delete_chat_yes_button = gtk_button_new_with_label ("Yes");
    gtk_widget_set_name(GTK_WIDGET(delete_chat_yes_button), "delete_chat_yes_button");
    gtk_button_set_relief(GTK_BUTTON(delete_chat_yes_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(delete_chat_box_for_buttons), delete_chat_yes_button, FALSE, FALSE, 0);

    GtkWidget *delete_chat_no_button = gtk_button_new_with_label ("No");
    gtk_widget_set_name(GTK_WIDGET(delete_chat_no_button), "delete_chat_no_button");
    gtk_button_set_relief(GTK_BUTTON(delete_chat_no_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(delete_chat_box_for_buttons), delete_chat_no_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(delete_chat_yes_button), "button_press_event", G_CALLBACK(delete_chat), NULL);
    g_signal_connect(G_OBJECT(delete_chat_no_button), "button_press_event", G_CALLBACK(unpress_logout), main_data.main_box.delete_chat_event_box);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.delete_chat_event_box));
}
