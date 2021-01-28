#include "Chat.h"
static char* int_to_str(int num) {
   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}

void display_message(char *message_text) {
    /*GtkWidget* photo_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(photo_chat_box), "top_chat_photo_box");
    gtk_container_add(GTK_CONTAINER(photo_chat_box), top_chat_avatar);
    gtk_box_pack_start(GTK_BOX(top_area), photo_chat_box, FALSE, FALSE, 10);*/

    GtkWidget *message = gtk_label_new(message_text);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    gtk_box_pack_start(GTK_BOX(left_box), message, FALSE, FALSE, 0);

    gtk_widget_show_all(left_box);
}

void send_message(GtkWidget *widget, GdkEventButton *event, gpointer *messsage) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        GtkTextIter start, end;
        gchar *text;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)messsage);

        gtk_text_buffer_get_bounds (buffer, &start, &end);
        text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
        printf("messsage: %s\n", text);
        display_message(text);
        
        g_free (text);
        gtk_text_view_set_buffer ((GtkTextView *)messsage, NULL);
    }
}

void smile_menu(GtkWidget *widget, GdkEventButton *event) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
    }
}

static void chat_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int chat_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    printf("Chat_id: %d\n", chat_id);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
}

static void emoji_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    int emoji_id = atoi((char*)gtk_label_get_text(GTK_LABEL(parent->data)));
    printf("Emoji: %d\n", emoji_id);
}

void event_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}
void event_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}
void unpress_event_box(GtkWidget *widget, GdkEventButton *event, gpointer *p) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        gtk_widget_unset_state_flags(GTK_WIDGET((GtkWidget *)p), GTK_STATE_FLAG_ACTIVE);
        gtk_widget_destroy(widget);
    }
}
void show_emoji_box(GtkWidget *widget){
        
        GtkWidget *emoji_event_box = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(emoji_event_box), "emoji_event_box");
        gtk_widget_set_size_request(GTK_WIDGET(emoji_event_box), 1400, 900);
        g_signal_connect(G_OBJECT(emoji_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
        gtk_fixed_put(GTK_FIXED(activity_block), emoji_event_box, 0, 0);

        GtkWidget *position_emoji_box = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(emoji_event_box), position_emoji_box);

        GtkWidget *emoji_event_box_for_click = gtk_event_box_new();
        gtk_widget_set_halign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
        gtk_widget_set_valign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
        g_signal_connect(G_OBJECT(emoji_event_box_for_click), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
        gtk_fixed_put(GTK_FIXED(position_emoji_box), emoji_event_box_for_click, 1400-280, 900-420);

        GtkWidget *emoji_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(emoji_box), "emoji_box");
        gtk_container_add(GTK_CONTAINER(emoji_event_box_for_click), emoji_box);

        GtkWidget *scrollable_emoji = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_size_request(GTK_WIDGET(scrollable_emoji), 200, 300);
        gtk_box_pack_start(GTK_BOX(emoji_box), scrollable_emoji, FALSE, FALSE, 0);

        GtkWidget *emoji_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(emoji_grid), 10);
        gtk_grid_set_column_spacing(GTK_GRID(emoji_grid), 10);

        GtkWidget *emoji_label = gtk_label_new("Emoji");
        gtk_widget_set_name(GTK_WIDGET(emoji_label), "emoji_label");
        gtk_grid_attach(GTK_GRID(emoji_grid), emoji_label, 1, 0, 6, 1);

        int sticker_num = 1;
        GtkWidget *single_emoji;
        
        for(int i = 1; i <= 11; i++)    // Columns
        {
            for(int j = 1; j <= 6; j++) // Rows
            {
                //single_emoji = create_list(sticker_num);
                single_emoji = gtk_event_box_new();
                GtkWidget *key = gtk_label_new(int_to_str(sticker_num));
                gtk_widget_set_name(GTK_WIDGET(key), "hidden");
                gtk_container_add(GTK_CONTAINER(single_emoji), key);

                gtk_widget_set_size_request(GTK_WIDGET(single_emoji), 25, 25);
                gtk_grid_attach(GTK_GRID(emoji_grid), single_emoji, j, i, 1, 1);
                gtk_widget_set_name(GTK_WIDGET(single_emoji), "emoji");
                g_signal_connect(G_OBJECT(single_emoji), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
                g_signal_connect(G_OBJECT(single_emoji), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
                g_signal_connect(G_OBJECT(single_emoji), "button_press_event", G_CALLBACK(emoji_click), NULL);
                sticker_num++;
                if(sticker_num > 82) break;
            }
        }
        gtk_container_add(GTK_CONTAINER(scrollable_emoji), emoji_grid);

        gtk_widget_show_all(GTK_WIDGET(emoji_event_box));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
}
void show_chat_settings(GtkWidget *widget){

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
        
        GtkWidget *chat_settings_event_box = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_settings_event_box), "chat_settings_event_box");
        gtk_widget_set_size_request(GTK_WIDGET(chat_settings_event_box), 1400, 900);
        g_signal_connect(G_OBJECT(chat_settings_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
        gtk_fixed_put(GTK_FIXED(activity_block), chat_settings_event_box, 0, 0);

        GtkWidget *position_chat_settings = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(chat_settings_event_box), position_chat_settings);

        GtkWidget *clickable_chat_settings = gtk_event_box_new();
        gtk_widget_set_halign(GTK_WIDGET(clickable_chat_settings), GTK_ALIGN_END);
        gtk_widget_set_valign(GTK_WIDGET(clickable_chat_settings), GTK_ALIGN_END);
        g_signal_connect(G_OBJECT(clickable_chat_settings), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
        gtk_fixed_put(GTK_FIXED(position_chat_settings), clickable_chat_settings, 1400-380, 900-860);

        GtkWidget *chat_settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_settings_box), "chat_settings_box");
        gtk_container_add(GTK_CONTAINER(clickable_chat_settings), chat_settings_box);

        GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_size_request(GTK_WIDGET(scrollable), 280, 350);
        gtk_box_pack_start(GTK_BOX(chat_settings_box), scrollable, FALSE, FALSE, 0);

        gtk_widget_show_all(GTK_WIDGET(chat_settings_event_box));
}



void main_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl) {
    GtkWidget **activity_block = (GtkWidget **)activity_bl;
    gtk_widget_destroy(GTK_WIDGET(main_data.login_box));
    if (widget) {}
    if(event->type != GDK_BUTTON_PRESS && event->button != 1){
        return;
    }

    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "resource/styles/main_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.main_screen_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_screen_box), "main_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_screen_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(*activity_block), main_data.main_screen_box, 0, 0);

//////////gtk_fixed
    GtkWidget *main_fixed = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_fixed), 300, 100);
    gtk_container_add(GTK_CONTAINER(main_data.main_screen_box), main_fixed);

    GtkWidget *up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(up_box), "up_box");
    gtk_widget_set_size_request(GTK_WIDGET(up_box), 300, 100);
    gtk_fixed_put(GTK_FIXED(main_fixed), up_box, 3, 3);

///////////////chat bar
    GtkWidget *chats[15];

    GtkWidget *chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_fixed), chat_bar, 3, 107);
    
    GtkWidget *chat_bar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(chat_bar_scroll), 200, 767);
    gtk_box_pack_start(GTK_BOX(chat_bar), chat_bar_scroll, TRUE, TRUE, 0);   

    GtkWidget *chat_bar_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(chat_bar_scroll), chat_bar_for_scroll);

    for(int i = 0; i < 15; i++) {
        GtkWidget *chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_button), "chat_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(chat_bar_for_scroll), chat_button, FALSE, FALSE, 0);

        chats[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chats[i]), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(chats[i]), 30, 30);
        gtk_container_add(GTK_CONTAINER(chat_button), chats[i]);
        
        GtkWidget *left_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(left_chat_avatar), 40, 40);
        char *path;
        if(i < 5) {
            path = strdup("resource/images/button.png");
        }else if(i < 10) {
            path = strdup("resource/images/start.png");
        } else {
            path = strdup("resource/images/font-emoji-svg-png-icon-free-download-389350-onlinewebfonts-play-button-image-11563230644rbzu7hlann.png");
        }
        g_signal_connect(G_OBJECT(left_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

        GtkWidget* photo_chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(photo_chat), "left_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(photo_chat), left_chat_avatar);
        //gtk_widget_set_size_request(GTK_WIDGET(photo_chat), 50, 30);
        gtk_box_pack_start(GTK_BOX(chats[i]), photo_chat, FALSE, FALSE, 10);

        GtkWidget* name_chat = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(name_chat), "chat_name");
        gtk_box_pack_start(GTK_BOX(chats[i]), name_chat, FALSE, FALSE, 10);

        GtkWidget *key = gtk_label_new(int_to_str(i));
        gtk_box_pack_start(GTK_BOX(chats[i]), key, FALSE, FALSE, 10);
        gtk_widget_set_name(GTK_WIDGET(key), "hidden");
        g_signal_connect(G_OBJECT(chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "button_press_event", G_CALLBACK(chat_click), NULL);
    }

///////////////
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(left_box), "left_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_box), WINDOW_SIZE_X - 315, WINDOW_SIZE_Y - 6);
    gtk_fixed_put(GTK_FIXED(main_fixed), left_box, 310, 3);

    /*GtkWidget *left_mid_box = gtk_label_new("Who you want to write?");
    gtk_widget_set_name(GTK_WIDGET(left_mid_box), "left_mid_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_mid_box), 200, 30);
    gtk_box_pack_start(GTK_BOX(left_box), left_mid_box, TRUE, FALSE, 0);*/
//////////////

//////////Chat_Screen
    //////Top area
    GtkWidget *top_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(top_area), "top_area");
    gtk_widget_set_size_request(GTK_WIDGET(top_area), 100, 70);
    gtk_box_pack_start(GTK_BOX(left_box), top_area, FALSE, FALSE, 0);
        
        //////Chat Logo
       GtkWidget *top_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(top_chat_avatar), 40, 40);
        char *path1 = strdup("resource/images/button.png");
        g_signal_connect(G_OBJECT(top_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), path1);

        GtkWidget* photo_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(photo_chat_box), "top_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(photo_chat_box), top_chat_avatar);
        gtk_box_pack_start(GTK_BOX(top_area), photo_chat_box, FALSE, FALSE, 10);
        //////Chat Name
        GtkWidget* chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(chat_name_box), "top_chat_name_box");
        gtk_box_pack_start(GTK_BOX(top_area), chat_name_box, FALSE, FALSE, 10);

        GtkWidget* top_chat_name = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(top_chat_name), "top_chat_name");
        gtk_container_add(GTK_CONTAINER(chat_name_box), top_chat_name);

        //////Online status
        /*GtkWidget* online_status_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(online_status_box), "online_status_box");
        gtk_box_pack_start(GTK_BOX(top_area), online_status_box, FALSE, FALSE, 10);

        GtkWidget* online_status = gtk_label_new("Offline");
        gtk_widget_set_name(GTK_WIDGET(online_status), "online_status");
        gtk_container_add(GTK_CONTAINER(online_status_box), online_status);*/

        /////Chat settings
        GtkWidget *chat_setting_button = gtk_event_box_new();
        gtk_box_pack_end(GTK_BOX(top_area), chat_setting_button, FALSE, FALSE, 10);
        gtk_widget_set_name(GTK_WIDGET(chat_setting_button), "chat_setting_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_setting_button), TRUE);

        g_signal_connect(G_OBJECT(chat_setting_button), "button_press_event", G_CALLBACK(show_chat_settings), NULL);

        GtkWidget *chat_setting_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(chat_setting_button_box), "chat_setting_button_box");
        gtk_widget_set_size_request(GTK_WIDGET(chat_setting_button_box), 18, 18);
        gtk_container_add(GTK_CONTAINER(chat_setting_button), chat_setting_button_box);

    //////Bottom area
    GtkWidget *bottom_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(bottom_area), "bottom_area");
    gtk_widget_set_size_request(GTK_WIDGET(bottom_area), 100, 70);
    gtk_box_pack_end(GTK_BOX(left_box), bottom_area, FALSE, FALSE, 0);

    GtkWidget *scrolled_message =  gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(GTK_WIDGET(scrolled_message), "scrollable_msg");
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_message), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_message, 100, 60); 
    gtk_box_pack_end(GTK_BOX(bottom_area), scrolled_message, FALSE, FALSE, 0);

    GtkWidget *msg_enter = gtk_text_view_new();
    gtk_widget_set_name(GTK_WIDGET(msg_enter), "msg_enter");
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(msg_enter), GTK_WRAP_WORD_CHAR);
    gtk_container_add(GTK_CONTAINER(scrolled_message), msg_enter);

    ////////////user_photo
    GtkWidget *user_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_avatar), 55, 55);
    char *path = strdup("resource/images/start.png");
    g_signal_connect(G_OBJECT(user_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

    GtkWidget *user_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(user_photo), "user_photo");
    gtk_container_add(GTK_CONTAINER(user_photo), user_avatar);
    gtk_box_pack_start(GTK_BOX(up_box), user_photo, FALSE, FALSE, 0);

    /*GtkWidget *user_image = gtk_image_new_from_file("resource/images/sh.jpg");
    align(user_image, 0.5f, 0.5f);
    add_style(user_image, "user_image", styles);
    gtk_container_add(GTK_CONTAINER(user_photo), user_image);*/
    ///////////settings_button

    GtkWidget *settings_button_clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(settings_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(settings_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), settings_button_clickable, 250, 10);

    GtkWidget *settings_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(settings_button), "settings_button");
    gtk_widget_set_size_request(GTK_WIDGET(settings_button), 18, 18);
    gtk_container_add(GTK_CONTAINER(settings_button_clickable), settings_button);

    g_signal_connect(G_OBJECT(settings_button_clickable), "button_press_event", G_CALLBACK(register_screen), (gpointer **)activity_bl);
    ////////////

    ///////////exit_button

    GtkWidget *exit_button_clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(exit_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(exit_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), exit_button_clickable, 280, 10);

    GtkWidget *exit_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    gtk_widget_set_size_request(GTK_WIDGET(exit_button), 18, 18);
    gtk_container_add(GTK_CONTAINER(exit_button_clickable), exit_button);

    g_signal_connect(G_OBJECT(exit_button_clickable), "button_press_event", G_CALLBACK(gtk_main_quit), NULL);
    //////////

///////send anc smile 
    GtkWidget *send_button_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(send_button_clickable), "send_button_clickable");
    gtk_widget_set_halign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), send_button_clickable, 1360, 853);

    GtkWidget *send_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(send_button), "send_button");
    gtk_widget_set_size_request(GTK_WIDGET(send_button), 18, 18);
    gtk_container_add(GTK_CONTAINER(send_button_clickable), send_button);

    g_signal_connect(G_OBJECT(send_button_clickable), "button_press_event", G_CALLBACK(send_message), msg_enter);

    GtkWidget *smile_button_clickable = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(smile_button_clickable), "smile_button_clickable");
    gtk_widget_set_halign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), smile_button_clickable, 1332, 853);

    g_signal_connect(G_OBJECT(smile_button_clickable), "button_press_event", G_CALLBACK(show_emoji_box), NULL);

    GtkWidget *smile_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(smile_button), "smile_button");
    gtk_widget_set_size_request(GTK_WIDGET(smile_button), 18, 18);
    gtk_container_add(GTK_CONTAINER(smile_button_clickable), smile_button);

    g_signal_connect(G_OBJECT(send_button_clickable), "button_press_event", G_CALLBACK(smile_menu), NULL);
    //g_signal_connect(G_OBJECT(smile_button_clickable), "button_press_event", G_CALLBACK(smile_menu), NULL);

    gtk_widget_show_all(main_data.main_screen_box);
}
