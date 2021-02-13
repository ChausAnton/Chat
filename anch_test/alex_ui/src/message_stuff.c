#include "Chat.h"

void *scrolling_msg() {

    usleep(50000);
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(main_data.main_box.messages_area_scroll));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));

    gtk_widget_hide(main_data.main_box.messages_area_scroll);
    gtk_widget_show(main_data.main_box.messages_area_scroll);

    return NULL;
}

void display_message(char *message_text) {
    
    GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
    gtk_box_pack_start(GTK_BOX(main_data.main_box.messanges_area_for_scroll), message_body, FALSE, FALSE, 0);

    GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_pack_end(GTK_BOX(message_body), message_body_box, FALSE, FALSE, 0);

    GtkWidget *message = gtk_label_new(message_text);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    gtk_box_pack_start(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);

    ///Time
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
    
    GtkWidget *message_time = gtk_label_new(asctime(tm));
    gtk_widget_set_name(GTK_WIDGET(message_time), "message_time");
    gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(message_body_box), message_time, FALSE, FALSE, 0);

    pthread_t display_thread = NULL;
    pthread_create(&display_thread, NULL, scrolling_msg, NULL);

    gtk_widget_show_all(main_data.main_box.right_chat_box);
}

void send_message(GtkWidget *widget, GdkEventButton *event, gpointer *messsage) {
    barashka = false;
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        GtkTextIter start, end;
        gchar *text;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)messsage);

        gtk_text_buffer_get_bounds (buffer, &start, &end);
        text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
        text = mx_strtrim(text);
        if(strlen(text) == 0) return;

        int msg_index = user_data.chat_array[main_data.main_box.search_chat_index].count_msg;

        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].msg_id_in_chat = msg_index+1; //Msg id in selected chat
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].chat_id = main_data.main_box.search_chat_id;//Chat id where msg
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].user_id = user_data.user_id;//User send id
        
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

        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].date = strdup(asctime(tm)); //Date of message
        user_data.chat_array[main_data.main_box.search_chat_index].msg_list[msg_index].text = strdup(text);//Text of message

        user_data.chat_array[main_data.main_box.search_chat_index].count_msg++;
        display_message(text);

        mx_printerr("Behind serever send\n");

        char *s_message = clear_client_message(NULL);

        send(sock, "@message_send", strlen("@message_send"), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock, thread_info, strlen(thread_info), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        mx_printerr("Into serever send\n");
        
        send(sock, text, strlen(text), 0);
        recv(sock, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        mx_printerr("After serever send\n");
        g_free (text);
        gtk_text_view_set_buffer ((GtkTextView *)messsage, NULL);
        barashka = true;

    }
}

void send_message_file(GtkWidget *widget) {

    GtkWidget *dialog = gtk_file_chooser_dialog_new("User image", GTK_WINDOW(main_data.window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gint run = gtk_dialog_run(GTK_DIALOG(dialog));

    if (run == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);

        gchar *source_path = gtk_file_chooser_get_filename(chooser);

        gchar *filename = source_path;

        while (strchr(filename, '/') != NULL) {
            filename = strchr(filename, '/');
            filename++;
        }

        GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
        gtk_box_pack_start(GTK_BOX(main_data.main_box.messanges_area_for_scroll), message_body, FALSE, FALSE, 0);

        GtkWidget *message_body_box_with_time = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        gtk_box_pack_end(GTK_BOX(message_body), message_body_box_with_time, FALSE, TRUE, 0);

        GtkWidget *message_body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        gtk_box_pack_start(GTK_BOX(message_body_box_with_time), message_body_box, FALSE, TRUE, 0);
        gtk_widget_set_name(GTK_WIDGET(message_body_box), "message");

        GtkWidget *message_file = gtk_image_new();

        GdkPixbuf *message_file_pixbuf = gdk_pixbuf_new_from_file(source_path, NULL);
        gint width = gdk_pixbuf_get_width(message_file_pixbuf);
        gint height = gdk_pixbuf_get_height(message_file_pixbuf);

        if (width > 200 || height > 200) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), gdk_pixbuf_new_from_file_at_scale(source_path, 200, 200, TRUE, NULL));
        } else {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), message_file_pixbuf);
        }

        g_object_unref(G_OBJECT(message_file_pixbuf));

        gtk_box_pack_start(GTK_BOX(message_body_box), message_file, FALSE, TRUE, 0);

        /*if (widget) {}
        if(event->type == GDK_BUTTON_PRESS && event->button == 1){
            GtkTextIter start, end;
            gchar *text;
            GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)messsage);

            gtk_text_buffer_get_bounds (buffer, &start, &end);
            text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
            
            if(strlen(text) != 0){
                GtkWidget *message = gtk_label_new(text);
                gtk_widget_set_name(GTK_WIDGET(message), "message_with_file");
                gtk_widget_set_halign(GTK_WIDGET(message), GTK_ALIGN_START);
                gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
                gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
                gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
                gtk_box_pack_end(GTK_BOX(message_body_box), message, FALSE, FALSE, 0);
            }*/

            ///Time
            /*time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            char *time_message = strdup(int_to_str(timeinfo->tm_hour));
            time_message = mx_strjoin(time_message, ":");
            if(timeinfo->tm_min < 10){
                time_message = mx_strjoin(time_message, "0");
            }
            time_message = mx_strjoin(time_message, int_to_str(timeinfo->tm_min));
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);*/

            time_t t = time(NULL);
            struct tm *tm = localtime(&t);

            GtkWidget *message_time = gtk_label_new(asctime(tm));
            gtk_widget_set_name(GTK_WIDGET(message_time), "message_time");
            gtk_widget_set_halign(GTK_WIDGET(message_time), GTK_ALIGN_END);
            gtk_box_pack_start(GTK_BOX(message_body_box_with_time), message_time, FALSE, FALSE, 0);

            pthread_t display_thread = NULL;
            pthread_create(&display_thread, NULL, scrolling_msg, NULL);
 
            //gtk_text_view_set_buffer ((GtkTextView *)messsage, NULL);
        //}
        gtk_widget_show_all(main_data.main_box.right_chat_box);

        ///Add to db
        char* path_for_db = strdup("$");
        path_for_db = mx_strjoin(path_for_db, int_to_str(main_data.main_box.search_chat_id));
        path_for_db = mx_strjoin(path_for_db, "$");
        path_for_db = mx_strjoin(path_for_db, filename);
        
        ///Creating dir
        char *dir_path = strdup("resource/cache/");
        dir_path = mx_strjoin(dir_path, int_to_str(main_data.main_box.search_chat_id));
        mkdir(dir_path, S_IRWXU | S_IRWXG | S_IRWXO);

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
    }
    gtk_widget_destroy (dialog);

    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}
