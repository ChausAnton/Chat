#include "Chat.h"

void event_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void event_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
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

void unpress_event_box(GtkWidget *widget, GdkEventButton *event, gpointer *p) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        gtk_widget_unset_state_flags(GTK_WIDGET((GtkWidget *)p), GTK_STATE_FLAG_ACTIVE);
        gtk_widget_destroy(widget);
    }
}

void unpress_chat_settings(GtkWidget *widget, GdkEventButton *event) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        //gtk_widget_unset_state_flags(GTK_WIDGET(main_data.main_box.chat_settings_button), GTK_STATE_FLAG_ACTIVE);
        gtk_widget_destroy(widget);
        //gtk_widget_destroy(main_data.main_box.chat_settings_event_box);
    }
}

static void unset_active_chats() {
    for(int i = 0; i < user_data.amount_of_chat; i++){
        gtk_widget_unset_state_flags(GTK_WIDGET(user_data.chat_array[i].chat_button), GTK_STATE_FLAG_ACTIVE);
    }
}

void change_chat_photo(GtkWidget *widget) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("User image", GTK_WINDOW(main_data.window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gint run = gtk_dialog_run(GTK_DIALOG(dialog));

    if (run == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);

        gtk_widget_destroy(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo);

        user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_avatar), 100, 100);
        user_data.chat_array[main_data.main_box.search_chat_index].temp_source_path = gtk_file_chooser_get_filename(chooser);
        g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), user_data.chat_array[main_data.main_box.search_chat_index].temp_source_path);
        
        user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo), "user_settings_photo");
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo), user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_avatar);
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo_event_box), user_data.chat_array[main_data.main_box.search_chat_index].chat_settings_photo);
    }
    gtk_widget_destroy(dialog);
    gtk_widget_hide(main_data.main_box.edit_chat_event_box);
    gtk_widget_show_all(main_data.main_box.edit_chat_event_box);
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void change_user_photo(GtkWidget *widget) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("User image", GTK_WINDOW(main_data.window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gint run = gtk_dialog_run(GTK_DIALOG(dialog));

    if (run == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);

        gtk_widget_destroy(user_data.user_settings_photo);

        user_data.user_settings_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(user_data.user_settings_avatar), 100, 100);
        user_data.temp_image_path = gtk_file_chooser_get_filename(chooser);
        g_signal_connect(G_OBJECT(user_data.user_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), user_data.temp_image_path);
        
        user_data.user_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_data.user_settings_photo), "user_settings_photo");
        gtk_container_add(GTK_CONTAINER(user_data.user_settings_photo), user_data.user_settings_avatar);
        gtk_container_add(GTK_CONTAINER(user_data.user_settings_photo_event_box), user_data.user_settings_photo);
    }
    gtk_widget_destroy(dialog);
    gtk_widget_hide(main_data.main_box.user_settings_event_box);
    gtk_widget_show_all(main_data.main_box.user_settings_event_box);
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void change_theme_to_default(GtkWidget *widget) {
    if(widget){}
    main_data.main_box.css = "resource/styles/main_screen.css";
    main_data.login_box.css = "resource/styles/sign_in.css";
    main_data.reg_box.css = "resource/styles/sign_up.css";

    gtk_css_provider_load_from_path(main_data.styles, main_data.main_box.css, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    gtk_widget_destroy(main_data.main_box.change_theme_event_box);
}

void change_theme_to_dark(GtkWidget *widget) {
    if(widget){}
    main_data.main_box.css = "resource/styles/main_screen_dark_theme.css";
    main_data.login_box.css = "resource/styles/sign_in_dark_theme.css";
    main_data.reg_box.css = "resource/styles/sign_up_dark_theme.css";

    gtk_css_provider_load_from_path(main_data.styles, main_data.main_box.css, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_destroy(main_data.main_box.change_theme_event_box);
}

void chat_click(GtkWidget *widget) {
    barashka = false;
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int chat_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    
    unset_active_chats();
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    printf("Chat_id: %d\n", chat_id);
    
    main_data.main_box.search_chat_id = chat_id;
    for(int i = 0; i < user_data.amount_of_chat; i++){
        if(user_data.chat_array[i].chat_id == chat_id){
            main_data.main_box.search_chat_index = i;
            break;
        }
    }
    printf("Search_chat_index: %d\n", main_data.main_box.search_chat_index);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));

    load_right_chat_box();
    display_loaded_messages();
    
    thread_info = strdup(mx_itoa(chat_id));

    barashka = true; 
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
            show_edit_chat(widget);
            break;
        case 2:
            show_add_new_user(widget);
            break;
        case 3:
            show_delete_user(widget);
            break;
        case 4:
            show_delete_chat(widget);
            break;
        default:
            break;
    }
}
void log_empty() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.login_box.log_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login or password is empty"));

    gtk_widget_show_all(main_data.login_box.log_error_box);
}

void log_incorrect() {
    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.login_box.log_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Incorrect login or password"));

    gtk_widget_show_all(main_data.login_box.log_error_box);
}


void scroll_handler(GtkWidget *widget, GdkEvent *event) {
    if(widget&&event){}
    gtk_adjustment_set_step_increment(main_data.main_box.vadj, 69.0);
    if ( event->type == GDK_SCROLL ) {
        if ( event->scroll.direction == GDK_SCROLL_DOWN ) {          
            gtk_adjustment_set_value(main_data.main_box.vadj, gtk_adjustment_get_value(main_data.main_box.vadj) + gtk_adjustment_get_step_increment(main_data.main_box.vadj));
        }
        if ( event->scroll.direction == GDK_SCROLL_UP ) {
            gtk_adjustment_set_value(main_data.main_box.vadj, gtk_adjustment_get_value(main_data.main_box.vadj) - gtk_adjustment_get_step_increment(main_data.main_box.vadj));
        }
    }
}

void sign_in() {
    char *s_message = clear_client_message(NULL);

    send(sock, "@sign_in", strlen("@sign_in"), 0);
    recv(sock, s_message, 2000, 0);

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[0])));
    printf("login: %s\n", name);
    char *password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[1])));
    printf("password: %s\n", password);

    if(strlen(name) == 0 || strlen(password) == 0) {
        log_empty();
        s_message = clear_client_message(s_message);
        send(sock, "Empty", strlen("Empty"), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Empty back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
    }
    else {
        s_message = clear_client_message(s_message);
        send(sock, "Nice", strlen("Nice"), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Nice back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
        s_message = clear_client_message(s_message);
        send(sock, name, strlen(name), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Name back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
        s_message = clear_client_message(s_message);
        send(sock, password, strlen(password), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Pass back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
        if(strcmp(s_message, "@TRUE") == 0) {
            main_data.main_box.search_chat_id = -1;
            user_data.login = strdup(name);
            user_data.password = strdup(password);

            gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[0]), "");
            gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[1]), "");

            load_data_for_user();
            main_screen();
        } else {
            log_incorrect();
        }
    }
    free(s_message);
}

void reg_empty() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.reg_box.reg_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login or password is empty"));

    gtk_widget_show_all(main_data.reg_box.reg_error_box);
}

void reg_is_used() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.reg_box.reg_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login is used"));

    gtk_widget_show_all(main_data.reg_box.reg_error_box);
}
void passwords_doesnt_match() {
    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.reg_box.reg_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Passwords doesn`t match"));

    gtk_widget_show_all(main_data.reg_box.reg_error_box);
}

void sign_up() {
    char *s_message = clear_client_message(NULL);

    send(sock, "@sign_up", strlen("@sign_up"), 0);
    recv(sock, s_message, 2000, 0);
    //mx_printerr("Sign up back: ");
    //mx_printerr(s_message);
    //mx_printerr("\n");

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[0])));
    printf("login: %s\n", name);
    char *password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[1])));
    printf("password: %s\n", password);
    char *repeat_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[2])));
    printf("repeat password: %s\n", repeat_password);


    if(strlen(name) == 0 || strlen(password) == 0 || strlen(repeat_password) == 0) {
        reg_empty();
        s_message = clear_client_message(s_message);
        send(sock, "Empty", strlen("Empty"), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Sign in back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
    }
    else if(strcmp(password, repeat_password) != 0) {
        passwords_doesnt_match();
        s_message = clear_client_message(s_message);
        send(sock, "Match", strlen("Match"), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Pass not match in back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
    }
    else {
        s_message = clear_client_message(s_message);
        send(sock, "Nice", strlen("Nice"), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Nice back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");

        s_message = clear_client_message(s_message);
        send(sock, name, strlen(name), 0);
        recv(sock, s_message, 2000, 0);
        //mx_printerr("Name in back: ");
        //mx_printerr(s_message);
        //mx_printerr("\n");
        
        if (strcmp(s_message, "Name back") == 0) {
            s_message = clear_client_message(s_message);
            send(sock, password, strlen(password), 0);
            recv(sock, s_message, 2000, 0);
            //mx_printerr("Pass1 in back: ");
            //mx_printerr(s_message);
            //mx_printerr("\n");

            s_message = clear_client_message(s_message);
            send(sock, repeat_password, strlen(repeat_password), 0);
            recv(sock, s_message, 2000, 0);
            //mx_printerr("Pass2 in back: ");
            //mx_printerr(s_message);
            //mx_printerr("\n");

            if (strcmp(s_message, "@TRUE") == 0) {
                main_data.main_box.search_chat_id = -1;
                user_data.login = strdup(name);
                user_data.password = strdup(password);

                gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[0]), "");
                gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[1]), "");
                gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[2]), "");

                load_data_for_user();
                main_screen();
            }
        }
        else {
            reg_is_used();
        }

    }
    free(s_message);
}

void unpress_logout(GtkWidget *widget, GdkEventButton *event, gpointer *p) {

    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        gtk_widget_destroy((GtkWidget *)p);
    }
}

void exit_from_online() {
    thread_info = NULL;
    char *s_message = clear_client_message(NULL);
    send(sock, "@exit_from_online", strlen("@exit_from_online"), 0);
    recv(sock, s_message, 2000, 0);
    free(s_message);
    start_screen();
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

        g_signal_connect(G_OBJECT(yes_button), "button_press_event", G_CALLBACK(exit_from_online), NULL);
        g_signal_connect(G_OBJECT(no_button), "button_press_event", G_CALLBACK(unpress_logout), logout_event_box);

        gtk_widget_show_all(GTK_WIDGET(logout_event_box));
    }
}

void show_search_result(GtkWidget *widget, GdkEventButton *event, gpointer *user_input) {

    if(widget&&event){}
    char *search_input = mx_strtrim((char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget *)user_input))));
    if(strlen(search_input) != 0) {

        if (main_data.main_box.is_first_search_destroy == true) gtk_widget_destroy(main_data.main_box.search_chat_button);
        main_data.main_box.is_first_search_destroy = true;

        char *s_message = clear_client_message(NULL);
        send(sock, "@search", strlen("@search"), 0);
        recv(sock, s_message, 2000, 0);
        s_message = clear_client_message(s_message);

        send(sock, search_input, strlen(search_input), 0);
        recv(sock, s_message, 2000, 0);
        s_message = clear_client_message(s_message);

        main_data.main_box.search_chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(main_data.main_box.search_chat_button), "user_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(main_data.main_box.search_chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.add_chats_scrollable_box), main_data.main_box.search_chat_button, FALSE, FALSE, 0);

        GtkWidget *search_chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(search_chat_box), "user_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(search_chat_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(main_data.main_box.search_chat_button), search_chat_box);
        
        GtkWidget *add_new_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_avatar), 80, 80);
        ////Image path of searching user
        char *path = strdup("resource/images/user_icon.png");

        g_signal_connect(G_OBJECT(add_new_chat_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

        GtkWidget *add_new_chat_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(add_new_chat_photo), "add_new_chat_photo");
        gtk_container_add(GTK_CONTAINER(add_new_chat_photo), add_new_chat_avatar);
        gtk_widget_set_size_request(GTK_WIDGET(add_new_chat_photo), 50, 30);
        gtk_box_pack_start(GTK_BOX(search_chat_box), add_new_chat_photo, FALSE, FALSE, 0);

        ////Name of searching user
        send(sock, "@user_name", strlen("@user_name"), 0);
        recv(sock, s_message, 2000, 0);
        GtkWidget* user_name_in_search = gtk_label_new(s_message);
        char *temp_s_message = strdup(s_message);
        s_message = clear_client_message(s_message);
        gtk_widget_set_name(GTK_WIDGET(user_name_in_search), "user_name_in_search");
        gtk_box_pack_start(GTK_BOX(search_chat_box), user_name_in_search, FALSE, FALSE, 0);

        //////User_id of searching user
        send(sock, "@user_id", strlen("@user_id"), 0);
        recv(sock, s_message, 2000, 0);
        GtkWidget *user_id = gtk_label_new(s_message);
        s_message = clear_client_message(s_message);
        gtk_box_pack_start(GTK_BOX(search_chat_box), user_id, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(user_id), "hidden");

        g_signal_connect(G_OBJECT(main_data.main_box.search_chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
        g_signal_connect(G_OBJECT(main_data.main_box.search_chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);
        
        g_signal_connect(G_OBJECT(main_data.main_box.search_chat_button), "button_press_event", G_CALLBACK(search_user_click), NULL);

        if(strcmp(temp_s_message, "NULL_USERNAME") == 0){
            gtk_widget_destroy(search_chat_box);
        }
        else {
            gtk_widget_hide(main_data.main_box.add_new_chat_event_box);
            gtk_widget_show_all(main_data.main_box.add_new_chat_event_box);
        }
    }
}
