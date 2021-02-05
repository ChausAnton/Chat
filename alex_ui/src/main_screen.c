#include "Chat.h"

void main_screen() {
    gtk_widget_destroy(GTK_WIDGET(main_data.activity_block));
    
    gtk_css_provider_load_from_path(main_data.styles, "resource/styles/main_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    
    main_data.main_box.all_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.all_main_box), "main_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.all_main_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.all_main_box, 0, 0);

    // Gtk fixed
    GtkWidget *main_fixed = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_fixed), 300, 100);
    gtk_container_add(GTK_CONTAINER(main_data.main_box.all_main_box), main_fixed);
    
    // Chat bar
    main_data.main_box.chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_fixed), main_data.main_box.chat_bar, 0, 0);

        // Up box
        GtkWidget *up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(up_box), "up_box");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar), up_box, FALSE, FALSE, 0);

            // User photo
            GtkWidget *user_settings_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(user_settings_button), "user_settings_button");
            gtk_box_pack_start(GTK_BOX(up_box), user_settings_button, FALSE, FALSE, 0);

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
            GtkWidget *user_name_label = gtk_label_new("%username%");
            gtk_widget_set_halign(GTK_WIDGET(user_name_label), GTK_ALIGN_START);
            gtk_widget_set_name(GTK_WIDGET(user_name_label), "user_name_label");
            gtk_box_pack_start(GTK_BOX(up_box), user_name_label, FALSE, FALSE, 0);

            // Add new chat button
            GtkWidget *add_new_chat_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(add_new_chat_button), "add_new_chat_button");
            gtk_widget_set_halign(GTK_WIDGET(add_new_chat_button), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(add_new_chat_button), GTK_ALIGN_CENTER);
            gtk_fixed_put(GTK_FIXED(main_fixed), add_new_chat_button, 250, 10);

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
            gtk_fixed_put(GTK_FIXED(main_fixed), exit_button, 280, 10);

            g_signal_connect(G_OBJECT(exit_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(exit_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(exit_button), "button_press_event", G_CALLBACK(logout), NULL);

            GtkWidget *exit_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(exit_button_box), "exit_button_box");
            gtk_widget_set_size_request(GTK_WIDGET(exit_button_box), 19, 19);
            gtk_container_add(GTK_CONTAINER(exit_button), exit_button_box);
        
        // Chat list
        load_chat_list();

    // Chat box
    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_fixed), main_data.main_box.right_chat_box, 310, 0);

    if(main_data.main_box.search_chat_id != -1) {

        // Top area
        GtkWidget *top_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(top_area), "top_area");
        gtk_widget_set_size_request(GTK_WIDGET(top_area), WINDOW_SIZE_X - 310, 60);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), top_area, FALSE, FALSE, 0);
        
            // Chat logo
            GtkWidget *top_chat_button = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(top_chat_button), "top_chat_button");
            gtk_box_pack_start(GTK_BOX(top_area), top_chat_button, FALSE, FALSE, 0);

            g_signal_connect(G_OBJECT(top_chat_button), "button_press_event", G_CALLBACK(show_chat_info), NULL);

            GtkWidget *top_chat_avatar = gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_WIDGET(top_chat_avatar), 40, 40);
            char *chat_photo_path = strdup(user_data.chat_array[main_data.main_box.search_chat_id].image_path);
            g_signal_connect(G_OBJECT(top_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), chat_photo_path);

            GtkWidget* top_chat_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(top_chat_photo), "top_chat_photo");
            gtk_container_add(GTK_CONTAINER(top_chat_photo), top_chat_avatar);
            gtk_container_add(GTK_CONTAINER(top_chat_button), top_chat_photo);
            //gtk_box_pack_start(GTK_BOX(top_chat_button), top_chat_photo, FALSE, FALSE, 0);

            // Chat name
            GtkWidget* chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(chat_name_box), "top_chat_name_box");
            gtk_box_pack_start(GTK_BOX(top_area), chat_name_box, FALSE, FALSE, 0);

            GtkWidget* top_chat_name = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_id].chat_name);
            gtk_widget_set_name(GTK_WIDGET(top_chat_name), "top_chat_name");
            gtk_container_add(GTK_CONTAINER(chat_name_box), top_chat_name);

            // Chat settings
            GtkWidget *chat_setting_button = gtk_event_box_new();
            gtk_box_pack_end(GTK_BOX(top_area), chat_setting_button, FALSE, FALSE, 0);
            gtk_widget_set_name(GTK_WIDGET(chat_setting_button), "chat_setting_button");
            gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_setting_button), TRUE);

            g_signal_connect(G_OBJECT(chat_setting_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(chat_setting_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(chat_setting_button), "button_press_event", G_CALLBACK(show_chat_settings), NULL);

            GtkWidget *chat_setting_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(chat_setting_button_box), "chat_setting_button_box");
            gtk_widget_set_size_request(GTK_WIDGET(chat_setting_button_box), 18, 18);
            gtk_container_add(GTK_CONTAINER(chat_setting_button), chat_setting_button_box);

            // Chat's messages area
            GtkWidget *messages_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(messages_area), "messages_area");
            gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), messages_area, FALSE, FALSE, 0);
            //gtk_fixed_put(GTK_FIXED(main_fixed), messanges_area, 310, 73);
                
            main_data.main_box.messages_area_scroll = gtk_scrolled_window_new(NULL, NULL);
            gtk_scrolled_window_set_kinetic_scrolling(GTK_SCROLLED_WINDOW( main_data.main_box.messages_area_scroll), TRUE);
            gtk_widget_set_size_request(GTK_WIDGET( main_data.main_box.messages_area_scroll), 200, 760);
            gtk_box_pack_start(GTK_BOX(messages_area),  main_data.main_box.messages_area_scroll, TRUE, TRUE, 0);   

            main_data.main_box.messanges_area_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
            gtk_container_add(GTK_CONTAINER( main_data.main_box.messages_area_scroll),  main_data.main_box.messanges_area_for_scroll);

        // Bottom area
        GtkWidget *bottom_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_widget_set_name(GTK_WIDGET(bottom_area), "bottom_area");
        gtk_widget_set_size_request(GTK_WIDGET(bottom_area), 100, 60);
        gtk_box_pack_end(GTK_BOX(main_data.main_box.right_chat_box), bottom_area, FALSE, FALSE, 0);

            // Clip button
            GtkWidget *clip_event_box = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(clip_event_box), "clip_event_box");
            gtk_widget_set_halign(GTK_WIDGET(clip_event_box), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(clip_event_box), GTK_ALIGN_CENTER);
            gtk_box_pack_start(GTK_BOX(bottom_area), clip_event_box, FALSE, FALSE, 0);

            GtkWidget *clip_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(clip_box), "clip_box");
            gtk_widget_set_size_request(GTK_WIDGET(clip_box), 20, 20);
            gtk_container_add(GTK_CONTAINER(clip_event_box), clip_box);

            g_signal_connect(G_OBJECT(clip_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(clip_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            // Message area
            GtkWidget *scrolled_message =  gtk_scrolled_window_new(NULL, NULL);
            gtk_widget_set_name(GTK_WIDGET(scrolled_message), "scrollable_msg");
            gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_message), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
            gtk_widget_set_size_request(scrolled_message, 700, 30); 
            gtk_box_pack_start(GTK_BOX(bottom_area), scrolled_message, TRUE, TRUE, 0);

            GtkWidget *msg_enter = gtk_text_view_new();
            gtk_widget_set_name(GTK_WIDGET(msg_enter), "msg_enter");
            gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(msg_enter), GTK_WRAP_WORD_CHAR);
            gtk_text_view_set_right_margin(GTK_TEXT_VIEW(msg_enter), 20);
            gtk_text_view_set_top_margin(GTK_TEXT_VIEW(msg_enter), 10);
            gtk_text_view_set_left_margin(GTK_TEXT_VIEW(msg_enter), 20);
            gtk_container_add(GTK_CONTAINER(scrolled_message), msg_enter);

            g_signal_connect(G_OBJECT(clip_event_box), "button_press_event", G_CALLBACK(send_message_file), msg_enter);
        
            // Emotes
            GtkWidget *smile_button_clickable = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(smile_button_clickable), "smile_button_clickable");
            gtk_widget_set_halign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
            gtk_box_pack_start(GTK_BOX(bottom_area), smile_button_clickable, FALSE, FALSE, 0);

            g_signal_connect(G_OBJECT(smile_button_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(smile_button_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(smile_button_clickable), "button_press_event", G_CALLBACK(show_emoji_box), NULL);

            GtkWidget *smile_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(smile_button), "smile_button");
            gtk_widget_set_size_request(GTK_WIDGET(smile_button), 20, 20);
            gtk_container_add(GTK_CONTAINER(smile_button_clickable), smile_button);

            // Send message
            GtkWidget *send_button_clickable = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(send_button_clickable), "send_button_clickable");
            gtk_widget_set_halign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
            gtk_box_pack_start(GTK_BOX(bottom_area), send_button_clickable, FALSE, FALSE, 0);

            g_signal_connect(G_OBJECT(send_button_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(send_button_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            GtkWidget *send_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
            gtk_widget_set_name(GTK_WIDGET(send_button), "send_button");
            gtk_widget_set_size_request(GTK_WIDGET(send_button), 18, 18);
            gtk_container_add(GTK_CONTAINER(send_button_clickable), send_button);

        g_signal_connect(G_OBJECT(send_button_clickable), "button_press_event", G_CALLBACK(send_message), msg_enter);

    } else {

        GtkWidget *right_mid_box = gtk_label_new("Whom you want to write?");
        gtk_widget_set_name(GTK_WIDGET(right_mid_box), "right_mid_box");
        gtk_widget_set_size_request(GTK_WIDGET(right_mid_box), 240, 40);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), right_mid_box, TRUE, FALSE, 0);
    }
    gtk_widget_show_all(main_data.activity_block);
}
