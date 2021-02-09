#include "../inc/Chat.h"

void load_messages_for_chat(int index, char *msg){

        /////Split
        char **str = mx_strsplit(msg, '#');
        for(int h = 0; str[h] != NULL; h++) {
            mx_printerr(str[h]);
            mx_printerr("\n");
        }
        mx_printerr("Bruh3\n");
        int j = 0;
        mx_printerr(mx_itoa(index));
        mx_printerr("Bruh4\n");
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].global_msg_id = atoi(str[j]); //Global msg in in selected chat
        j++;
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].msg_id_in_chat = atoi(str[j]); //Msg id in selected chat
        j++;
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].chat_id = atoi(str[j]);//Chat id where msg
        j++;
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].user_id = atoi(str[j]);//User send id
        j++;
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date = strdup(str[j]); //Date of message
        j++;
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text = strdup(str[j]);//Text of message
        j++;

        mx_printerr("Bruh5s\n");
        
        GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.messanges_area_for_scroll), message_body, FALSE, FALSE, 0);

        mx_printerr("Bruh6s\n");
        
        GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_pack_end(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

        mx_printerr("Bruh7s\n");
        GtkWidget *message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text);
        gtk_widget_set_name(GTK_WIDGET(message), "message");
        gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
        gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
        gtk_box_pack_start(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);
        mx_printerr("Bruh8s\n");
        ///Time
        GtkWidget *message_time = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date);
        gtk_widget_set_name(GTK_WIDGET(message_time), "message_time");
        gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
        gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);

        mx_printerr("Bruh9s\n");
}

void load_right_chat_box() {
    gtk_widget_destroy(main_data.main_box.right_chat_box);
    
    // Chat box
    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.right_chat_box, 310, 0);

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
            char *chat_photo_path = strdup(user_data.chat_array[main_data.main_box.search_chat_index].image_path);
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

            GtkWidget* top_chat_name = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].chat_name);
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

    gtk_widget_show_all(main_data.activity_block);
}
