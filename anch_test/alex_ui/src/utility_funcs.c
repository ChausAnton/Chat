#include "Chat.h"

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

static void unset_active_chats() {
    for(int i = 0; i < user_data.amount_of_chat; i++){
        gtk_widget_unset_state_flags(GTK_WIDGET(user_data.chat_array[i].chat_button), GTK_STATE_FLAG_ACTIVE);
    }
}

void chat_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int chat_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));

    unset_active_chats();
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    printf("Chat_id: %d\n", chat_id);
    main_data.main_box.search_chat_id = chat_id;
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
    load_right_chat_box();
}

void event_enter_notify_search(GtkWidget *widget) {
    if(gtk_widget_get_state_flags(GTK_WIDGET(widget)) & GTK_STATE_FLAG_ACTIVE) {
        return;
    } else {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void event_leave_notify_search(GtkWidget *widget) {
    if(gtk_widget_get_state_flags(GTK_WIDGET(widget)) & GTK_STATE_FLAG_ACTIVE) {
        return;
    } else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    }
}

void search_user_click(GtkWidget *widget) {

    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int user_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    //printf("Search_user_id: %d\n", user_id);

    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));

    if(gtk_widget_get_state_flags(GTK_WIDGET(widget)) & GTK_STATE_FLAG_ACTIVE) {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE);
        for(int i = 0; i < 100;  i++){
            if(new_chat_users_id[i] == user_id) new_chat_users_id[i] = -1;
        }
    } else {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
        //printf("Search_user_id: %d\n", user_id);
        for(int i = 0; i < 100;  i++){
            if(new_chat_users_id[i] == -1) {
                new_chat_users_id[i] = user_id;
                break;
            }
        }
    }
}

void chat_settings_click(GtkWidget *widget, GdkEventButton *event, gpointer *data) {

    if (widget&&event){}
    int number = *((int*)data);
    switch(number) {
        case 1:
            write(1, "Chat renamed!\n", 14);
            break;
        case 2:
            //write(1, "User added!\n", 12);
            show_add_new_user(widget);
            break;
        case 3:
            write(1, "User deleted!\n", 14);
            break;
        case 4:
            write(1, "Chat deleted!\n", 14);
            break;
        case 5:
            write(1, "Chat image changed!\n", 20);
            break;
        default:
            break;
    }
}

void sign_in() {
    char *s_message = clear_client_message(NULL);

    send(sock, "@sign_in", strlen("@sign_in"), 0);
    recv(sock, s_message, 2000, 0);

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[0])));
    printf("login: %s\n", name);
    char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[1])));
    printf("password: %s\n", passwrod);


    s_message = clear_client_message(s_message);
    send(sock, name, strlen(name), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);
    send(sock, passwrod, strlen(passwrod), 0);
    recv(sock, s_message, 2000, 0);
    mx_printerr(s_message);

    if(strcmp(s_message, "@TRUE") == 0) {
        main_data.main_box.search_chat_id = -1;
        user_data.login = strdup(name);
        user_data.password = strdup(passwrod);

        gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[0]), "");
        gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[1]), "");

        load_data_for_user();
        main_screen();
    }
    free(s_message);
}

void sign_up() {
    char *s_message = clear_client_message(NULL);

    send(sock, "@sign_up", strlen("@sign_up"), 0);
    recv(sock, s_message, 2000, 0);

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[0])));
    printf("login: %s\n", name);
    char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[1])));
    printf("password: %s\n", passwrod);
    char *repeat_passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[2])));
    printf("repeat password: %s\n", repeat_passwrod);

    s_message = clear_client_message(s_message);
    send(sock, name, strlen(name), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);

    send(sock, passwrod, strlen(passwrod), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);

    send(sock, repeat_passwrod, strlen(repeat_passwrod), 0);
    recv(sock, s_message, 2000, 0);
	mx_printerr(s_message);

    if(strcmp(s_message, "@TRUE") == 0) {
        main_data.main_box.search_chat_id = -1;
        user_data.login = strdup(name);
        user_data.password = strdup(passwrod);

        gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[0]), "");
        gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[1]), "");
        gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[2]), "");

        load_data_for_user();
        main_screen();
    }
    free(s_message);
}

void unpress_logout(GtkWidget *widget, GdkEventButton *event, gpointer *p) {

    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        gtk_widget_destroy((GtkWidget *)p);
    }
}

void logout(GtkWidget *widget, GdkEventButton *event) {

    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        //gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

        GtkWidget *logout_event_box = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(logout_event_box), "logout_event_box");
        gtk_widget_set_size_request(GTK_WIDGET(logout_event_box), 1400, 900);
        g_signal_connect(G_OBJECT(logout_event_box), "button_press_event", G_CALLBACK(gtk_widget_show), widget);
        //g_signal_connect(G_OBJECT(logout_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
        gtk_fixed_put(GTK_FIXED(main_data.activity_block), logout_event_box, 0, 0);

        GtkWidget *position_logout = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(logout_event_box), position_logout);

        GtkWidget *clickable_logout = gtk_event_box_new();
        gtk_widget_set_halign(GTK_WIDGET(clickable_logout), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(clickable_logout), GTK_ALIGN_CENTER);
        gtk_widget_set_size_request(GTK_WIDGET(clickable_logout), 300, 130);
        gtk_fixed_put(GTK_FIXED(position_logout), clickable_logout, 580, 300);
        g_signal_connect(G_OBJECT(clickable_logout), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

        GtkWidget *logout_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_widget_set_name(GTK_WIDGET(logout_box), "logout_box");
        gtk_container_add(GTK_CONTAINER(clickable_logout), logout_box);

        GtkWidget *logout_label = gtk_label_new("Are you sure you want to exit?");
        gtk_widget_set_name(GTK_WIDGET(logout_label), "logout_label");
        gtk_box_pack_start(GTK_BOX(logout_box), logout_label, FALSE, FALSE, 0);

        GtkWidget *logout_box_for_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        gtk_widget_set_name(GTK_WIDGET(logout_box_for_buttons), "logout_box_for_buttons");
        gtk_box_pack_start(GTK_BOX(logout_box), logout_box_for_buttons, FALSE, FALSE, 10);

        GtkWidget *yes_button = gtk_button_new_with_label ("Yes");
        gtk_widget_set_name(GTK_WIDGET(yes_button), "yes_button");
        gtk_button_set_relief(GTK_BUTTON(yes_button), GTK_RELIEF_NONE);
        gtk_box_pack_start(GTK_BOX(logout_box_for_buttons), yes_button, FALSE, FALSE, 0);

        GtkWidget *no_button = gtk_button_new_with_label ("No");
        gtk_widget_set_name(GTK_WIDGET(no_button), "no_button");
        gtk_button_set_relief(GTK_BUTTON(no_button), GTK_RELIEF_NONE);
        gtk_box_pack_start(GTK_BOX(logout_box_for_buttons), no_button, FALSE, FALSE, 0);

        g_signal_connect(G_OBJECT(yes_button), "button_press_event", G_CALLBACK(start_screen), NULL);
        g_signal_connect(G_OBJECT(no_button), "button_press_event", G_CALLBACK(unpress_logout), logout_event_box);

        gtk_widget_show_all(GTK_WIDGET(logout_event_box));
    }
}


void show_search_result(GtkWidget *widget, GdkEventButton *event, gpointer *user_input) {
    char *s_message = clear_client_message(NULL);
    send(sock, "@search", strlen("@search"), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);

    if(widget&&event){}
    char *search_input = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget *)user_input)));
    send(sock, search_input, strlen(search_input), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);

    GtkWidget *search_chat_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(search_chat_button), "user_button");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(search_chat_button), TRUE);
    gtk_box_pack_start(GTK_BOX(main_data.main_box.add_chats_scrollable_box), search_chat_button, FALSE, FALSE, 0);

    GtkWidget *search_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(search_chat_box), "user_small_box");
    gtk_widget_set_size_request(GTK_WIDGET(search_chat_box), 300, 70);
    gtk_container_add(GTK_CONTAINER(search_chat_button), search_chat_box);
    
    GtkWidget *add_new_chat_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_avatar), 80, 80);
    ////Image path of searching user
    char *path = strdup("resource/images/sh.jpg");

    g_signal_connect(G_OBJECT(add_new_chat_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

    GtkWidget *add_new_chat_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(add_new_chat_photo), "add_new_chat_photo");
    gtk_container_add(GTK_CONTAINER(add_new_chat_photo), add_new_chat_avatar);
    gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_photo), 50, 30);
    gtk_box_pack_start(GTK_BOX(search_chat_box), add_new_chat_photo, FALSE, FALSE, 0);

    ////Name of searching user
    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    GtkWidget* user_name_in_search = gtk_label_new(s_message);
    s_message = clear_client_message(s_message);
    gtk_widget_set_name(GTK_WIDGET(user_name_in_search), "user_name_in_search");
    gtk_box_pack_start(GTK_BOX(search_chat_box), user_name_in_search, FALSE, FALSE, 0);

    //////User_id of searching user
    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    GtkWidget *user_id = gtk_label_new(s_message);
    s_message = clear_client_message(s_message);
    gtk_box_pack_start(GTK_BOX(search_chat_box), user_id, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(user_id), "hidden");

    g_signal_connect(G_OBJECT(search_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(search_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);
    
    g_signal_connect(G_OBJECT(search_chat_button), "button_press_event", G_CALLBACK(search_user_click), NULL);

    gtk_widget_hide(main_data.main_box.add_new_chat_event_box);
    gtk_widget_show_all(main_data.main_box.add_new_chat_event_box);

}
