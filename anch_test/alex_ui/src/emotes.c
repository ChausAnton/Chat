#include "Chat.h"

void *scrolling_sticker() {

    usleep(3000);
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(main_data.main_box.messages_area_scroll));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    gtk_widget_show_all(main_data.main_box.right_chat_box);
    return NULL;
}

void emoji_click(GtkWidget *widget, GdkEventButton *event, gpointer *sticker_path) {
    barashka = false;
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(message_body), "message_body");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

        GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_pack_end(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

        GtkWidget *message_file = gtk_image_new();
        GdkPixbuf *message_file_pixbuf = gdk_pixbuf_new_from_file((gchar *)sticker_path, NULL);
        
        gint width = gdk_pixbuf_get_width(message_file_pixbuf);
        gint height = gdk_pixbuf_get_height(message_file_pixbuf);

        if (width > 52 || height > 52) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), gdk_pixbuf_new_from_file_at_scale((gchar *)sticker_path, 52, 52, TRUE, NULL));
        } else {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), message_file_pixbuf);
        }
        g_object_unref(G_OBJECT(message_file_pixbuf));

        gtk_box_pack_start(GTK_BOX(message_body_box), message_file, FALSE, FALSE, 0);
        
        /*time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            char *time_message = strdup(int_to_str(timeinfo->tm_hour));
            time_message = mx_strjoin(time_message, ":");
            if(timeinfo->tm_min < 10){
                time_message = mx_strjoin(time_message, "0");
        }
        time_message = mx_strjoin(time_message, int_to_str(timeinfo->tm_min));*/
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char **time_message = mx_strsplit(asctime(tm), ' ');

        GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));
        gtk_widget_set_name(GTK_WIDGET(message_time), "message_time_sticker");
        gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
        gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);

        ///Add to db
        char* sticker_num = mx_strsplit(mx_strsplit((char *)sticker_path, '_')[1], '.')[0];
        char* path_for_db = strdup("~");
        path_for_db = mx_strjoin(path_for_db, sticker_num);

        int msg_index = user_data.chat_array[main_data.main_box.search_chat_index].count_msg;

        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].msg_id_in_chat = msg_index+1; //Msg id in selected chat
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].chat_id = main_data.main_box.search_chat_id;//Chat id where msg
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].user_id = user_data.user_id;//User send id
        
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].date = strdup(asctime(tm)); //Date of message
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].text = strdup(path_for_db);//Text of message

        user_data.chat_array[main_data.main_box.search_chat_index].count_msg++;

        char *s_message = clear_client_message(NULL);

        send(sock, "@message_send", strlen("@message_send"), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock, thread_info, strlen(thread_info), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);
        
        send(sock, path_for_db, strlen(path_for_db), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        free(path_for_db);
        free(sticker_num);
        
        pthread_t display_thread = NULL;
        pthread_create(&display_thread, NULL, scrolling_sticker, NULL);

        barashka = true;
    }
    gtk_widget_destroy(main_data.main_box.emoji_event_box);
    gtk_widget_unset_state_flags(main_data.main_box.smile_button_clickable, GTK_STATE_FLAG_ACTIVE);
    gtk_widget_show_all(main_data.main_box.right_chat_box);
}

void show_emoji_box(GtkWidget *widget) {

    main_data.main_box.emoji_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.emoji_event_box), "emoji_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.emoji_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.emoji_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.emoji_event_box, 0, 0);

    GtkWidget *position_emoji_box = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.emoji_event_box), position_emoji_box);

    GtkWidget *emoji_event_box_for_click = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(emoji_event_box_for_click), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(position_emoji_box), emoji_event_box_for_click, 1125, 540);

    GtkWidget *emoji_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(emoji_box), "emoji_box");
    gtk_container_add(GTK_CONTAINER(emoji_event_box_for_click), emoji_box);

    GtkWidget *scrollable_emoji = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable_emoji), 185, 265);
    gtk_box_pack_start(GTK_BOX(emoji_box), scrollable_emoji, FALSE, FALSE, 0);

    GtkWidget *emoji_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(emoji_grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(emoji_grid), 10);

    int sticker_num = 1;
    GtkWidget *single_emoji;
    
    for(int i = 2; i <= 11; i++) {
          for(int j = 1; j <= 3; j++) {
              single_emoji = gtk_event_box_new();  
              gtk_widget_set_name(GTK_WIDGET(single_emoji), "emoji");
              gtk_grid_attach(GTK_GRID(emoji_grid), single_emoji, j, i, 1, 1);

              GtkWidget *sticker_photo = gtk_drawing_area_new();
              gtk_widget_set_size_request(GTK_WIDGET(sticker_photo), 55, 55);
              char *path_sticker_photo = strdup("resource/images/stickers/sticker_");
              path_sticker_photo =  mx_strjoin(path_sticker_photo, int_to_str(sticker_num));
              path_sticker_photo =  mx_strjoin(path_sticker_photo, ".png");

              g_signal_connect(G_OBJECT(sticker_photo), "draw", G_CALLBACK(draw_sticker_photo), path_sticker_photo);
              gtk_container_add(GTK_CONTAINER(single_emoji), sticker_photo);

              g_signal_connect(G_OBJECT(single_emoji), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
              g_signal_connect(G_OBJECT(single_emoji), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

              g_signal_connect(G_OBJECT(single_emoji), "button_press_event", G_CALLBACK(emoji_click), (void *)path_sticker_photo);

              sticker_num++;
              if(sticker_num > 10) break;
          }
          if(sticker_num > 10) break;
    }
    gtk_container_add(GTK_CONTAINER(scrollable_emoji), emoji_grid);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.emoji_event_box));

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
}
