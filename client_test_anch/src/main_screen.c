#include "Chat.h"


/*void align(GtkWidget *widget, float x, float y) {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    gtk_misc_set_alignment(GTK_MISC(widget), x, y);
    #pragma clang diagnostic pop
}

void add_style(GtkWidget *widget, const gchar *class_name, GtkCssProvider *css) {
    css = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(css, class_name);
    gtk_style_context_add_provider(css, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);
}*/
static char* int_to_str(int num) {
   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}

static void s_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next;
    children = children->next;
    int sticker_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    printf("Sticker: %d\n", sticker_id);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
}

void event_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}
void event_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
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
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_screen_box), window_size_x, window_size_y);
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
    GtkWidget *chats[10];

    GtkWidget *chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_fixed), chat_bar, 3, 107);
    
    GtkWidget *chat_bar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(chat_bar_scroll), 200, 767);
    gtk_box_pack_start(GTK_BOX(chat_bar), chat_bar_scroll, TRUE, TRUE, 0);   

    GtkWidget *chat_bar_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(chat_bar_scroll), chat_bar_for_scroll);

    for(int i = 0; i < 10; i++) {
        GtkWidget *chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_button), "chat_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(chat_bar_for_scroll), chat_button, FALSE, FALSE, 0);

        chats[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chats[i]), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(chats[i]), 30, 30);
        gtk_container_add(GTK_CONTAINER(chat_button), chats[i]);

        GtkWidget* photo_chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(photo_chat), "chat_photo");
        gtk_widget_set_size_request(GTK_WIDGET(photo_chat), 60, 30);
        gtk_box_pack_start(GTK_BOX(chats[i]), photo_chat, FALSE, FALSE, 10);

        GtkWidget* name_chat = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(name_chat), "chat_name");
        gtk_box_pack_start(GTK_BOX(chats[i]), name_chat, FALSE, FALSE, 10);

        GtkWidget *key = gtk_label_new(int_to_str(i));
        gtk_box_pack_start(GTK_BOX(chats[i]), key, FALSE, FALSE, 10);
        gtk_widget_set_name(GTK_WIDGET(key), "hidden");
        g_signal_connect(G_OBJECT(chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "button_press_event", G_CALLBACK(s_click), NULL);
    }

///////////////
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(left_box), "left_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_box), window_size_x - 315, window_size_y - 6);
    gtk_fixed_put(GTK_FIXED(main_fixed), left_box, 310, 3);

    GtkWidget *left_mid_box = gtk_label_new("Who you want to write?");
    gtk_widget_set_name(GTK_WIDGET(left_mid_box), "left_mid_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_mid_box), 200, 30);
    gtk_box_pack_start(GTK_BOX(left_box), left_mid_box, TRUE, FALSE, 0);
//////////////
    ////////////user_photo
    GtkWidget *user_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(user_photo), "user_photo");
    gtk_widget_set_size_request(GTK_WIDGET(user_photo), 60, 30);
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

    gtk_widget_show_all(main_data.main_screen_box);
}
