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
        if(user_data.chat_array[i].chat_id == -1) continue;
        gtk_widget_unset_state_flags(GTK_WIDGET(user_data.chat_array[i].chat_button), GTK_STATE_FLAG_ACTIVE);
    }
}

void change_chat_photo(GtkWidget *widget) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("User image", GTK_WINDOW(main_data.window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gint run = gtk_dialog_run(GTK_DIALOG(dialog));

    if (run == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);

        gtk_widget_destroy(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo);

        user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar), 100, 100);
        user_data.chat_array[main_data.main_box.search_chat_id].temp_source_path = gtk_file_chooser_get_filename(chooser);
        g_signal_connect(G_OBJECT(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), user_data.chat_array[main_data.main_box.search_chat_id].temp_source_path);
        
        user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo), "user_settings_photo");
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo), user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_avatar);
        gtk_container_add(GTK_CONTAINER(user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo_event_box), user_data.chat_array[main_data.main_box.search_chat_id].chat_settings_photo);
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

void chat_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int chat_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));

    unset_active_chats();
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    printf("Chat_id: %d\n", chat_id);
    for (int i = 0; i < user_data.amount_of_chat; ++i) {
        if (user_data.chat_array[i].chat_id == chat_id)
        main_data.main_box.search_chat_id = i;
    }
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
    int user_id = atoi((char *)gtk_label_get_text(GTK_LABEL(children->data)));
    printf("Search_user_id: %d\n", user_id);

    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));

    if(gtk_widget_get_state_flags(GTK_WIDGET(widget)) & GTK_STATE_FLAG_ACTIVE) {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE);
        for(int i = 0; i < 100;  i++){
            if(new_chat_users_id[i] == user_id) {
                new_chat_users_id[i] = -1;
            }
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

void sign_in() {

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[0])));
    name = mx_strtrim(name);
    printf("login: %s\n", name);
    char *password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[1])));
    printf("password: %s\n", password);
    
    if(TRUE) {

        if(strcmp(name, "error") == 0) {
            incorrect_log_or_pswd();
        }
        else if(strlen(name) == 0) {
            empty_log();
        }
        else {
            main_data.main_box.search_chat_id = -1;
            user_data.login = strdup(name);
            user_data.password = strdup(password);

            gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[0]), "");
            gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[1]), "");

            load_data_for_user();
            main_screen();
        }
    }
}

void sign_up() {

    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[0])));
    name = mx_strtrim(name);
    printf("login: %s\n", name);
    char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[1])));
    printf("password: %s\n", passwrod);
    char *repeat_passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[2])));
    printf("repeat password: %s\n", repeat_passwrod);

    if(TRUE) {

        if(strcmp(name, "error") == 0) {
            log_is_used();
        }
        else if(strlen(name) == 0) {
            empty_reg_log();
        }
        else {
            main_data.main_box.search_chat_id = -1;
            user_data.login = strdup(name);
            user_data.password = strdup(passwrod);

            gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[0]), "");
            gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[1]), "");
            gtk_entry_set_text(GTK_ENTRY(main_data.reg_box.sign_up_data[2]), "");
            
            load_data_for_user();
            main_screen();
        }
    }
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

    if(widget&&event){}
    char *search_input = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget *)user_input)));
    printf("search_input:%s\n", search_input);
}

void empty_log() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.login_box.log_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login is empty"));

    gtk_widget_show_all(main_data.login_box.log_error_box);
}

void incorrect_log_or_pswd() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.login_box.log_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Incorrect login or password"));

    gtk_widget_show_all(main_data.login_box.log_error_box);
}

void empty_reg_log() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.reg_box.reg_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login is empty"));

    gtk_widget_show_all(main_data.reg_box.reg_error_box);
}

void log_is_used() {

    GList *children = gtk_container_get_children(GTK_CONTAINER(main_data.reg_box.reg_error_box));
    
    gtk_label_set_text(GTK_LABEL(children->data), strdup("Login is used"));

    gtk_widget_show_all(main_data.reg_box.reg_error_box);
}

void added_same_user_to_chat() {

    GtkWidget *added_same_user_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(added_same_user_event_box), "logout_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(added_same_user_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(added_same_user_event_box), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), added_same_user_event_box, 0, 0);

    GtkWidget *position_added_same_user = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(added_same_user_event_box), position_added_same_user);

    GtkWidget *clickable_added_same_user = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable_added_same_user), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable_added_same_user), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(clickable_added_same_user), 300, 130);
    gtk_fixed_put(GTK_FIXED(position_added_same_user), clickable_added_same_user, 580, 300);
    g_signal_connect(G_OBJECT(clickable_added_same_user), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

    GtkWidget *added_same_user_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(added_same_user_box), "logout_box");
    gtk_container_add(GTK_CONTAINER(clickable_added_same_user), added_same_user_box);

    GtkWidget *added_same_user_label = gtk_label_new("The user is currently in this chat");
    gtk_widget_set_name(GTK_WIDGET(added_same_user_label), "added_same_user_label");
    gtk_box_pack_start(GTK_BOX(added_same_user_box), added_same_user_label, FALSE, FALSE, 0);

    GtkWidget *added_same_user_box_for_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_name(GTK_WIDGET(added_same_user_box_for_buttons), "added_same_user_box_for_buttons");
    gtk_box_pack_start(GTK_BOX(added_same_user_box), added_same_user_box_for_buttons, FALSE, FALSE, 10);

    GtkWidget *ok_button = gtk_button_new_with_label ("Ok");
    gtk_widget_set_name(GTK_WIDGET(ok_button), "ok_button");
    gtk_widget_set_halign(GTK_WIDGET(clickable_added_same_user), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable_added_same_user), GTK_ALIGN_CENTER);
    gtk_button_set_relief(GTK_BUTTON(ok_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(added_same_user_box_for_buttons), ok_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(ok_button), "button_press_event", G_CALLBACK(unpress_logout), added_same_user_event_box);

    gtk_widget_show_all(GTK_WIDGET(added_same_user_event_box));
}
