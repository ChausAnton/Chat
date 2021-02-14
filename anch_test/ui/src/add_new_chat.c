#include "../inc/Chat.h"

void show_add_new_chat(GtkWidget *widget) {
    
    main_data.main_box.is_first_search_destroy = false;

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    main_data.main_box.add_new_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.add_new_chat_event_box), "add_new_chat_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.add_new_chat_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.add_new_chat_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.add_new_chat_event_box, 0, 0);

    GtkWidget *position_add_new_chat = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.add_new_chat_event_box), position_add_new_chat);

    GtkWidget *clickable_add_new_chat = gtk_event_box_new();
    //gtk_widget_set_name(GTK_WIDGET(clickable_add_new_chat), "clickable_add_new_chat");
    gtk_widget_set_halign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_add_new_chat), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
  
    gtk_fixed_put(GTK_FIXED(position_add_new_chat), clickable_add_new_chat, 640, 120);

    GtkWidget *add_new_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(add_new_chat_box), "add_new_chat_box");
    gtk_container_add(GTK_CONTAINER(clickable_add_new_chat), add_new_chat_box);

    GtkWidget *horizontal_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(horizontal_box), "horizontal_box");
    gtk_widget_set_size_request(GTK_WIDGET(horizontal_box), 400, 20);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), horizontal_box, FALSE, FALSE, 0);

    GtkWidget *search_users = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_users), "search_users");
    gtk_entry_set_max_length(GTK_ENTRY(search_users), 30);
    gtk_entry_set_placeholder_text (GTK_ENTRY(search_users), "Search");
    gtk_box_pack_start(GTK_BOX(horizontal_box), search_users, TRUE, TRUE, 0);

    // Search button
    GtkWidget *search_users_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(search_users_button), "search_users_button");
    gtk_widget_set_size_request(GTK_WIDGET(search_users_button), 40, 40);
    gtk_widget_set_halign(GTK_WIDGET(search_users_button), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable_add_new_chat), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(horizontal_box), search_users_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(search_users_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(search_users_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

    g_signal_connect(G_OBJECT(search_users_button), "button_press_event", G_CALLBACK(show_search_result), search_users);

    GtkWidget *search_users_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(search_users_button_box), "search_users_button_box");
    gtk_container_add(GTK_CONTAINER(search_users_button), search_users_button_box);

    // Scroll
    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 520);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), scrollable, FALSE, FALSE, 0);

    main_data.main_box.add_chats_scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET( main_data.main_box.add_chats_scrollable_box), "add_chats_scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable),  main_data.main_box.add_chats_scrollable_box);
    
    GtkWidget *new_chat_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(new_chat_event_box), "new_chat_event_box");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(new_chat_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(add_new_chat_box), new_chat_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(new_chat_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(new_chat_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *new_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(new_chat_box), "new_chat_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(new_chat_box), 280, 70);
    gtk_container_add(GTK_CONTAINER(new_chat_event_box), new_chat_box);

    GtkWidget *new_chat_box_label = gtk_label_new("New chat");
    gtk_widget_set_name(GTK_WIDGET(new_chat_box_label), "new_chat_box_label");
    gtk_widget_set_halign(GTK_WIDGET(new_chat_box_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(new_chat_box_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(new_chat_box), new_chat_box_label, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(new_chat_event_box), "button_press_event", G_CALLBACK(add_new_chat), NULL);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.add_new_chat_event_box));
}


static void scrolling_chats() {
    while (gtk_events_pending()) {
        gtk_main_iteration();
        GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(main_data.main_box.chat_bar_scroll));
        gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj) - gtk_adjustment_get_page_size(adj));
        gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(main_data.main_box.chat_bar_scroll), adj);
        gtk_main_iteration();
    }
}

void add_new_chat_from_server(int chat_id_num, int sock_to) { 
    user_data.chat_array[user_data.amount_of_chat].msg_list = (t_message *)malloc(sizeof(t_message) * 30000);
    user_data.chat_array[user_data.amount_of_chat].count_msg = 0;

    char *s_message = clear_client_message(NULL);
    send(sock_to, "@chat_name", strlen("@chat_name"), 0);
    recv(sock_to, s_message, 1000, 0);
    user_data.chat_array[user_data.amount_of_chat].chat_name = strdup(s_message);//Вернусть с базы данных имя этого чата
    s_message = clear_client_message(s_message);

    send(sock_to, "@count_users", strlen("@count_users"), 0);
    recv(sock_to, s_message, 1000, 0);
    user_data.chat_array[user_data.amount_of_chat].count_users = atoi(s_message);//Вернуть с базы даных количество юзеров
    s_message = clear_client_message(s_message);
    user_data.chat_array[user_data.amount_of_chat].users_list = (t_foreign_user *)malloc(sizeof(t_foreign_user) * 100);
    for(int i = 0; i < user_data.chat_array[user_data.amount_of_chat].count_users; i++){
            send(sock_to, "@user_id", strlen("@user_id"), 0);
            recv(sock_to, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[i].user_id = atoi(s_message);
            s_message = clear_client_message(s_message);

            send(sock_to, "@login", strlen("@login"), 0);
            recv(sock_to, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[i].login = strdup(s_message);
            s_message = clear_client_message(s_message);

            send(sock_to, "@name", strlen("@name"), 0);
            recv(sock_to, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[i].name = strdup(s_message);
            //mx_printerr("name : ");
            //mx_printerr(s_message);
             //mx_printerr("\n");
            s_message = clear_client_message(s_message);

            send(sock_to, "@image_path", strlen("@image_path"), 0);
            recv(sock_to, s_message, 1000, 0);

            user_data.chat_array[user_data.amount_of_chat].users_list[i].image_path = strdup(s_message);
            s_message = clear_client_message(s_message);
    } ///Эту всю информацию о юзерах которые есть в чате ты должен получать с базы данных
   
    user_data.chat_array[user_data.amount_of_chat].chat_id = chat_id_num;

    //Пока не трогать сильно
    //user_data.chat_array[user_data.amount_of_chat].image_path = strdup("ui/resource/images/stickers/sticker_50.png");
    user_data.chat_array[user_data.amount_of_chat].image_path = strdup("ui/resource/images/stickers/sticker_");
    user_data.chat_array[user_data.amount_of_chat].image_path = mx_strjoin(user_data.chat_array[user_data.amount_of_chat].image_path, int_to_str(user_data.amount_of_chat+1));
    user_data.chat_array[user_data.amount_of_chat].image_path = mx_strjoin(user_data.chat_array[user_data.amount_of_chat].image_path,  ".png");

    //Остальное не трогать
    user_data.chat_array[user_data.amount_of_chat].chat_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_button), "chat_button");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(user_data.chat_array[user_data.amount_of_chat].chat_button), TRUE);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar_for_scroll), user_data.chat_array[user_data.amount_of_chat].chat_button, FALSE, FALSE, 0);

    user_data.chat_array[user_data.amount_of_chat].chat_list_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_box), "chat_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_box), 300, 70);
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[user_data.amount_of_chat].chat_button), user_data.chat_array[user_data.amount_of_chat].chat_list_box);
    
    user_data.chat_array[user_data.amount_of_chat].chat_list_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_avatar), 40, 40);
    char *path = strdup(user_data.chat_array[user_data.amount_of_chat].image_path);
    user_data.chat_array[user_data.amount_of_chat].temp_source_path = user_data.chat_array[user_data.amount_of_chat].image_path;

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_list_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

    user_data.chat_array[user_data.amount_of_chat].chat_list_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), "left_chat_photo_box");
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), user_data.chat_array[user_data.amount_of_chat].chat_list_avatar);
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), 50, 30);
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), user_data.chat_array[user_data.amount_of_chat].chat_list_photo, FALSE, FALSE, 0);

    user_data.chat_array[user_data.amount_of_chat].chat_label_name = gtk_label_new(user_data.chat_array[user_data.amount_of_chat].chat_name);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_label_name), "chat_name");
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), user_data.chat_array[user_data.amount_of_chat].chat_label_name, FALSE, FALSE, 0);

    GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[user_data.amount_of_chat].chat_id));
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), chat_id, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "button_press_event", G_CALLBACK(chat_click), NULL);
    
    user_data.amount_of_chat++;
    
    gtk_widget_show_all(main_data.main_box.chat_bar);

    scrolling_chats();
}

void add_new_chat() { 
    barashka = false;
    //user_data.chat_array[user_data.amount_of_chat].msg_list = NULL;
    user_data.chat_array[user_data.amount_of_chat].msg_list = (t_message *)malloc(sizeof(t_message) * 30000);
    user_data.chat_array[user_data.amount_of_chat].count_msg = 0;

    char *s_message = clear_client_message(NULL);
    send(sock, "@new_chat", strlen("@new_chat"), 0);
    recv(sock, s_message, 1000, 0);
    s_message = clear_client_message(s_message);

    //int index_new = user_data.amount_of_chat;
    //user_data.amount_of_chat += 1;
    user_data.chat_array[user_data.amount_of_chat].chat_name = strdup("New Chat");
    user_data.chat_array[user_data.amount_of_chat].count_users = 1;
    
    for(int i = 0; i < 100; i++){
        if(new_chat_users_id[i] != -1) {
            user_data.chat_array[user_data.amount_of_chat].count_users += 1;
        }
    }

    send(sock, mx_itoa(user_data.chat_array[user_data.amount_of_chat].count_users), strlen(mx_itoa(user_data.chat_array[user_data.amount_of_chat].count_users)), 0);
    recv(sock, s_message, 1000, 0);

    user_data.chat_array[user_data.amount_of_chat].users_list = (t_foreign_user *)malloc(sizeof(t_foreign_user) * 100);
    int tmp_index = 0;
    for(int i = 0; i < 100; i++){
        if(new_chat_users_id[i] != -1) {
            send(sock, mx_itoa(new_chat_users_id[i]), strlen(mx_itoa(new_chat_users_id[i])), 0);
            recv(sock, s_message, 1000, 0);
            s_message = clear_client_message(s_message);

            user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].user_id = new_chat_users_id[i];

            send(sock, "@login", strlen("@login"), 0);
            recv(sock, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].login = strdup(s_message);
            s_message = clear_client_message(s_message);

            send(sock, "@name", strlen("@name"), 0);
            recv(sock, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].name = strdup(s_message);
            s_message = clear_client_message(s_message);

            send(sock, "@image_path", strlen("@image_path"), 0);
            recv(sock, s_message, 1000, 0);
            user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].image_path = strdup(s_message);
            s_message = clear_client_message(s_message);
            tmp_index++;
        }
    }
    user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].user_id = user_data.user_id;
    user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].login = strdup(user_data.login);
    user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].image_path = strdup(user_data.image_path);
    user_data.chat_array[user_data.amount_of_chat].users_list[tmp_index].name = strdup(user_data.name);

    s_message = clear_client_message(s_message);
    send(sock, "@chat_id", strlen("@chat_id"), 0);
    recv(sock, s_message, 1000, 0);
    user_data.chat_array[user_data.amount_of_chat].chat_id = atoi(s_message);
    s_message = clear_client_message(s_message);

    //user_data.chat_array[user_data.amount_of_chat].image_path = strdup("ui/resource/images/stickers/sticker_50.png");
    user_data.chat_array[user_data.amount_of_chat].image_path = strdup("ui/resource/images/stickers/sticker_");
    user_data.chat_array[user_data.amount_of_chat].image_path = mx_strjoin(user_data.chat_array[user_data.amount_of_chat].image_path, int_to_str(user_data.amount_of_chat+1));
    user_data.chat_array[user_data.amount_of_chat].image_path = mx_strjoin(user_data.chat_array[user_data.amount_of_chat].image_path,  ".png");

    user_data.chat_array[user_data.amount_of_chat].chat_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_button), "chat_button");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(user_data.chat_array[user_data.amount_of_chat].chat_button), TRUE);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.chat_bar_for_scroll), user_data.chat_array[user_data.amount_of_chat].chat_button, FALSE, FALSE, 0);

    user_data.chat_array[user_data.amount_of_chat].chat_list_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET( user_data.chat_array[user_data.amount_of_chat].chat_list_box), "chat_small_box");
    gtk_widget_set_size_request(GTK_WIDGET( user_data.chat_array[user_data.amount_of_chat].chat_list_box), 300, 70);
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[user_data.amount_of_chat].chat_button),  user_data.chat_array[user_data.amount_of_chat].chat_list_box);
    
    user_data.chat_array[user_data.amount_of_chat].chat_list_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_avatar), 40, 40);
    char *path = strdup(user_data.chat_array[user_data.amount_of_chat].image_path);
    user_data.chat_array[user_data.amount_of_chat].temp_source_path = user_data.chat_array[user_data.amount_of_chat].image_path;

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_list_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

    user_data.chat_array[user_data.amount_of_chat].chat_list_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), "left_chat_photo_box");
    gtk_container_add(GTK_CONTAINER(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), user_data.chat_array[user_data.amount_of_chat].chat_list_avatar);
    gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_list_photo), 50, 30);
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), user_data.chat_array[user_data.amount_of_chat].chat_list_photo, FALSE, FALSE, 0);

    user_data.chat_array[user_data.amount_of_chat].chat_label_name = gtk_label_new(user_data.chat_array[user_data.amount_of_chat].chat_name);
    gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[user_data.amount_of_chat].chat_label_name), "chat_name");
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), user_data.chat_array[user_data.amount_of_chat].chat_label_name, FALSE, FALSE, 0);

    GtkWidget *chat_id = gtk_label_new(int_to_str(user_data.chat_array[user_data.amount_of_chat].chat_id));
    gtk_box_pack_start(GTK_BOX(user_data.chat_array[user_data.amount_of_chat].chat_list_box), chat_id, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    g_signal_connect(G_OBJECT(user_data.chat_array[user_data.amount_of_chat].chat_button), "button_press_event", G_CALLBACK(chat_click), NULL);
    
    //pthread_t display_thread = NULL;
    //pthread_create(&display_thread, NULL, scrolling_chats, NULL);
    user_data.amount_of_chat++;
    for(int i = 0; i < 100; i++) new_chat_users_id[i] = -1;

    gtk_widget_destroy(main_data.main_box.add_new_chat_event_box); //Delete window

    //load_chat_list();
    
    gtk_widget_show_all(main_data.main_box.chat_bar);

    scrolling_chats();
    barashka = true;
}

