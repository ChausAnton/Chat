#include "../inc/Chat.h"

int is_sticker(char *txt){
    char *num = NULL;
    if(strncmp(txt, "~", 1) == 0){
        for(unsigned long i = 1; i < strlen(txt); i++){
            if(!mx_isdigit(txt[i])) return -1;
        }
        num = mx_strjoin(num, &txt[1]);
        if(atoi(num) < 51) return atoi(num);
        else  return -1;
    } else {
        return -1;
    }
}

void display_new_loaded_messages(int chat_id, int index) {
    chat_id++;
    int sticker_id = is_sticker(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text);
    if(index == 0 || strncmp(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index-1].date, 11) != 0){
        GtkWidget *date_change = gtk_label_new(strndup(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, 11));
        gtk_widget_set_name(GTK_WIDGET(date_change), "date_change");
        gtk_widget_set_halign (date_change, GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), date_change, FALSE, FALSE, 0);
    }
    if(sticker_id != -1){
        // Sticker
        if(user_data.user_id == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].user_id){
            char *sticker_path = strdup("ui/resource/images/stickers/sticker_");
            sticker_path = mx_strjoin(sticker_path, mx_itoa(sticker_id));
            sticker_path = mx_strjoin(sticker_path, ".png");

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

            char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, ' ');
            GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

            gtk_widget_set_name(GTK_WIDGET(message_time), "message_time_sticker");
            gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
            gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
        }
        else {
            char *sticker_path = strdup("ui/resource/images/stickers/sticker_");
            sticker_path = mx_strjoin(sticker_path, mx_itoa(sticker_id));
            sticker_path = mx_strjoin(sticker_path, ".png");

            GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            gtk_widget_set_name(GTK_WIDGET(message_body), "message_body");
            gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

            GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
            gtk_box_pack_start(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

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

            char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, ' ');
            GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

            gtk_widget_set_name(GTK_WIDGET(message_time), "obtained_message_time_sticker");
            gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_START);
            gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
        }
    } else {
        // Message
        if(user_data.user_id == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].user_id){
            GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            gtk_widget_set_name(GTK_WIDGET(message_body), "message_body");
            gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

            GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
            gtk_box_pack_end(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

            GtkWidget *message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text);
            gtk_widget_set_name(GTK_WIDGET(message), "message");
            gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
            gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
            gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
            gtk_box_pack_start(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);

            ///Time
            char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, ' ');
            GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

            gtk_widget_set_name(GTK_WIDGET(message_time), "message_time");
            gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
            gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
        }
        else {
            GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            gtk_widget_set_name(GTK_WIDGET(message_body), "obtained_message_body");
            gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

            GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
            gtk_box_pack_start(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

            for(int i = 0; i < user_data.chat_array[main_data.main_box.search_chat_index].count_users; i++){
                if(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].user_id 
                    == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].user_id){
                    GtkWidget *username_message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].users_list[i].name);
                    gtk_widget_set_name(GTK_WIDGET(username_message), "username_obtained_message_label");
                    gtk_widget_set_halign(GTK_WIDGET(username_message), GTK_ALIGN_START);
                    gtk_box_pack_start(GTK_BOX(message_body_box), username_message, FALSE, FALSE, 0);

                }
            }

            GtkWidget *message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text);
            gtk_widget_set_name(GTK_WIDGET(message), "obtained_message");
            gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
            gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
            gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
            gtk_box_pack_start(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);

            ///Time
            char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].date, ' ');
            GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

            gtk_widget_set_name(GTK_WIDGET(message_time), "obtained_message_time");
            gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_START);
            gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
        }
    }
    
    int height = (strlen(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[index].text) / 50 + 1) * 15;
    gtk_adjustment_set_upper(main_data.main_box.vadj, gtk_adjustment_get_upper(main_data.main_box.vadj) + height*height);
   
    if (gtk_adjustment_get_upper(main_data.main_box.vadj) > 1005) { // 1005 probably is 780 + msg_amnt * msg_height
        scrolling_msg();
    }
    
    gtk_widget_show_all(main_data.activity_block);
}

void display_loaded_messages() {
    for(int i = 0;  i < user_data.chat_array[main_data.main_box.search_chat_index].count_msg; i++){
        int sticker_id = is_sticker(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].text);
        if(i == 0 || strncmp(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i-1].date, 11) != 0){
            GtkWidget *date_change = gtk_label_new(strndup(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, 11));
            gtk_widget_set_name(GTK_WIDGET(date_change), "date_change");
            gtk_widget_set_halign (date_change, GTK_ALIGN_CENTER);
            gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), date_change, FALSE, FALSE, 0);
        }
        if(sticker_id != -1){
            // Sticker
            if(user_data.user_id == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].user_id){
                char *sticker_path = strdup("ui/resource/images/stickers/sticker_");
                sticker_path = mx_strjoin(sticker_path, mx_itoa(sticker_id));
                sticker_path = mx_strjoin(sticker_path, ".png");

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

                char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, ' ');
                GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

                gtk_widget_set_name(GTK_WIDGET(message_time), "message_time_sticker");
                gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
                gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
            } else {
                char *sticker_path = strdup("ui/resource/images/stickers/sticker_");
                sticker_path = mx_strjoin(sticker_path, mx_itoa(sticker_id));
                sticker_path = mx_strjoin(sticker_path, ".png");

                GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
                gtk_widget_set_name(GTK_WIDGET(message_body), "message_body");
                gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

                GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
                gtk_box_pack_start(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

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

                char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, ' ');
                GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

                gtk_widget_set_name(GTK_WIDGET(message_time), "obtained_message_time_sticker");
                gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_START);
                gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
            }
        } else {
            // Message
            if(user_data.user_id == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].user_id){
                GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
                gtk_widget_set_name(GTK_WIDGET(message_body), "message_body");
                gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), message_body, FALSE, FALSE, 0);

                GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
                gtk_box_pack_end(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);
            
                GtkWidget *message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].text);
                gtk_widget_set_name(GTK_WIDGET(message), "message");
                gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
                gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
                gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
                gtk_box_pack_start(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);

                ///Time
                char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, ' ');
                GtkWidget *message_time = gtk_label_new(strndup(time_message[3], 5));

                gtk_widget_set_name(GTK_WIDGET(message_time), "message_time");
                gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
                gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);
            }
            else {
                GtkWidget *obtained_message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
                gtk_widget_set_name(GTK_WIDGET(obtained_message_body), "obtained_message_body");
                gtk_box_pack_start(GTK_BOX(main_data.main_box.messages_area_for_scroll), obtained_message_body, FALSE, FALSE, 0);

                GtkWidget *obtained_message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
                gtk_box_pack_start(GTK_BOX(obtained_message_body), obtained_message_body_box, FALSE, FALSE, 0);
                
                for(int j = 0; j < user_data.chat_array[main_data.main_box.search_chat_index].count_users; j++){
                    if(user_data.chat_array[main_data.main_box.search_chat_index].users_list[j].user_id 
                        == user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].user_id){
                        GtkWidget *username_obtained_message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].users_list[j].name);
                        gtk_widget_set_name(GTK_WIDGET(username_obtained_message), "username_obtained_message_label");
                        gtk_widget_set_halign(GTK_WIDGET(username_obtained_message), GTK_ALIGN_START);
                        gtk_box_pack_start(GTK_BOX(obtained_message_body_box), username_obtained_message, FALSE, FALSE, 0);
            
                    }
                }

                GtkWidget *obtained_message = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].text);
                gtk_widget_set_name(GTK_WIDGET(obtained_message), "obtained_message");
                gtk_label_set_line_wrap(GTK_LABEL(obtained_message), TRUE);
                gtk_label_set_line_wrap_mode(GTK_LABEL(obtained_message), PANGO_WRAP_WORD_CHAR);
                gtk_label_set_max_width_chars(GTK_LABEL(obtained_message), 50);
                gtk_box_pack_start(GTK_BOX(obtained_message_body_box), obtained_message, FALSE, FALSE, 0);

                ///Time
                char **time_message = mx_strsplit(user_data.chat_array[main_data.main_box.search_chat_index].msg_list[i].date, ' ');
                GtkWidget *obtained_message_time = gtk_label_new(strndup(time_message[3], 5));

                gtk_widget_set_name(GTK_WIDGET(obtained_message_time), "obtained_message_time");
                gtk_widget_set_halign(GTK_WIDGET(obtained_message_time), GTK_ALIGN_START);
                gtk_box_pack_start(GTK_BOX(obtained_message_body_box), obtained_message_time, FALSE, FALSE, 0);
            }
        }       
    }
    gtk_adjustment_set_upper(main_data.main_box.vadj, gtk_adjustment_get_upper(main_data.main_box.vadj) + 65.0*65.0);
    scrolling_msg();
    gtk_widget_show_all(main_data.activity_block);
}

void load_messages_for_chat(int chat_id, int index, char *msg, int last){  
    int chat_index = -1;
    for(int i = 0; i < user_data.amount_of_chat; i++){
        if(user_data.chat_array[i].chat_id == chat_id) {
            chat_index = i;
            break;
        }
    }
    
    /////Split
    char **str = mx_strsplit(msg, '#');
    int j = 0;
    user_data.chat_array[chat_index].msg_list[index].global_msg_id = atoi(str[j]); //Global msg in in selected chat
    j++;
    user_data.chat_array[chat_index].msg_list[index].msg_id_in_chat = atoi(str[j]); //Msg id in selected chat
    j++;
    user_data.chat_array[chat_index].msg_list[index].chat_id = atoi(str[j]);//Chat id where msg
    j++;
    user_data.chat_array[chat_index].msg_list[index].user_id = atoi(str[j]);//User send id
    j++;
    user_data.chat_array[chat_index].msg_list[index].date = strdup(str[j]); //Date of message
    j++;
    user_data.chat_array[chat_index].msg_list[index].text = strdup(str[j]);//Text of message
    j++;
    if(chat_id == main_data.main_box.search_chat_id) display_new_loaded_messages(chat_id, index);
    
    if(last){}
    /*if(last == 1) {
        gtk_widget_hide(main_data.main_box.right_chat_box);
        gtk_widget_show_all(main_data.main_box.right_chat_box);
    }*/
}

void load_right_chat_box() {
    gtk_widget_destroy(main_data.main_box.right_chat_box);
    
    // Chat box
    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.right_chat_box, 310, 0);

        // Top area
        GtkWidget *top_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(top_area), "top_area");
        gtk_widget_set_size_request(GTK_WIDGET(top_area), WINDOW_SIZE_X - 310, 60);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), top_area, FALSE, FALSE, 0);

            // Chat logo
            user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box = gtk_event_box_new();
            //gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box), "user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box");
            gtk_box_pack_start(GTK_BOX(top_area), user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box, FALSE, FALSE, 0);
            g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box), "button_press_event", G_CALLBACK(show_chat_info), NULL);

            user_data.chat_array[main_data.main_box.search_chat_index].chat_box_avatar = gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_avatar), 40, 40);


            char *chat_photo_path = strdup(user_data.chat_array[main_data.main_box.search_chat_index].image_path);
            g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_avatar), "draw", G_CALLBACK(draw_chat_avatar), chat_photo_path);

            user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            //gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo), "top_chat_photo");
            gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo), user_data.chat_array[main_data.main_box.search_chat_index].chat_box_avatar);
            gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo_event_box), user_data.chat_array[main_data.main_box.search_chat_index].chat_box_photo);

            // Chat name
            GtkWidget* chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(chat_name_box), "top_chat_name_box");
            gtk_box_pack_start(GTK_BOX(top_area), chat_name_box, FALSE, FALSE, 0);

            main_data.main_box.chat_box_name_label = gtk_label_new(user_data.chat_array[main_data.main_box.search_chat_index].chat_name);
            gtk_label_set_selectable(GTK_LABEL(main_data.main_box.chat_box_name_label), TRUE);
            //gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_box_name_label), "top_chat_name");
            gtk_container_add(GTK_CONTAINER(chat_name_box), main_data.main_box.chat_box_name_label);

            // Chat settings
            main_data.main_box.chat_settings_button = gtk_event_box_new();
            gtk_box_pack_end(GTK_BOX(top_area), main_data.main_box.chat_settings_button, FALSE, FALSE, 0);
            gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_settings_button), "chat_settings_button");
            gtk_event_box_set_above_child(GTK_EVENT_BOX(main_data.main_box.chat_settings_button), TRUE);

            g_signal_connect(G_OBJECT(main_data.main_box.chat_settings_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(main_data.main_box.chat_settings_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(main_data.main_box.chat_settings_button), "button_press_event", G_CALLBACK(show_chat_settings), NULL);

            GtkWidget *chat_settings_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            //gtk_widget_set_name(GTK_WIDGET(chat_settings_button_box), "chat_settings_button_box");
            gtk_widget_set_size_request(GTK_WIDGET(chat_settings_button_box), 18, 18);
            gtk_container_add(GTK_CONTAINER(main_data.main_box.chat_settings_button), chat_settings_button_box);

        // Chat's messages area
        GtkWidget *chatting_area_event_box = gtk_event_box_new();
        gtk_widget_set_events(GTK_WIDGET(chatting_area_event_box), GDK_SCROLL_MASK);
        gtk_widget_set_size_request(GTK_WIDGET(chatting_area_event_box), 200, 200);
        gtk_widget_set_name(GTK_WIDGET(chatting_area_event_box), "messages_area");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), chatting_area_event_box, FALSE, FALSE, 0);

        GtkWidget *chatting_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chatting_area), "messages_area");
        gtk_container_add(GTK_CONTAINER(chatting_area_event_box), chatting_area);
  
            main_data.main_box.messages_area_scroll = gtk_scrolled_window_new(NULL, NULL);
            gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.messages_area_scroll), WINDOW_SIZE_X - 310, 780);
            gtk_box_pack_start(GTK_BOX(chatting_area),  main_data.main_box.messages_area_scroll, FALSE, FALSE, 0);

            main_data.main_box.vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(main_data.main_box.messages_area_scroll)); 

            g_signal_connect(main_data.main_box.messages_area_scroll, "scroll_event", G_CALLBACK(scroll_handler), NULL);
            
            main_data.main_box.messages_area_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
            gtk_container_add(GTK_CONTAINER(main_data.main_box.messages_area_scroll),  main_data.main_box.messages_area_for_scroll);

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
            //g_signal_connect(G_OBJECT(clip_event_box), "button_press_event", G_CALLBACK(obtained_message_file), msg_enter);

            // Emotes
            main_data.main_box.smile_button_clickable = gtk_event_box_new();
            gtk_widget_set_name(GTK_WIDGET(main_data.main_box.smile_button_clickable), "smile_button_clickable");
            gtk_widget_set_halign(GTK_WIDGET(main_data.main_box.smile_button_clickable), GTK_ALIGN_CENTER);
            gtk_widget_set_valign(GTK_WIDGET(main_data.main_box.smile_button_clickable), GTK_ALIGN_CENTER);
            gtk_box_pack_start(GTK_BOX(bottom_area), main_data.main_box.smile_button_clickable, FALSE, FALSE, 0);

            g_signal_connect(G_OBJECT(main_data.main_box.smile_button_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(main_data.main_box.smile_button_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(main_data.main_box.smile_button_clickable), "button_press_event", G_CALLBACK(show_emoji_box), NULL);

            GtkWidget *smile_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(smile_button), "smile_button");
            gtk_widget_set_size_request(GTK_WIDGET(smile_button), 20, 20);
            gtk_container_add(GTK_CONTAINER(main_data.main_box.smile_button_clickable), smile_button);

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
