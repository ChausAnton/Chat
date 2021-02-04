#include "Chat.h"

void show_user_settings(GtkWidget *widget) {

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    GtkWidget *user_settings_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(user_settings_event_box), "user_settings_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(user_settings_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(user_settings_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(activity_block), user_settings_event_box, 0, 0);

    GtkWidget *position_user_settings = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(user_settings_event_box), position_user_settings);

    GtkWidget *clickable_user_settings = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable_user_settings), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_user_settings), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_user_settings), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
  
    gtk_fixed_put(GTK_FIXED(position_user_settings), clickable_user_settings, 630, 350);


    GtkWidget *user_settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(user_settings_box), "user_settings_box");
    gtk_container_add(GTK_CONTAINER(clickable_user_settings), user_settings_box);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 200);
    gtk_box_pack_start(GTK_BOX(user_settings_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(scrollable_box), "scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), scrollable_box);

    GtkWidget *user_settings_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_settings_avatar), 100, 100);
    char *path = strdup("resource/images/start.png");
    g_signal_connect(G_OBJECT(user_settings_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), path);

    GtkWidget *user_settings_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_settings_photo), "user_settings_photo");
    gtk_container_add(GTK_CONTAINER(user_settings_photo), user_settings_avatar);
    gtk_box_pack_start(GTK_BOX(scrollable_box), user_settings_photo, FALSE, FALSE, 0);

    GtkWidget *user_nickname = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(user_nickname), "user_nickname");
    gtk_entry_set_max_length(GTK_ENTRY(user_nickname), 30);
    /*char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(sign_in_data[0])));
    printf("login: %s\n", name);*/
    gtk_entry_set_placeholder_text (GTK_ENTRY(user_nickname), "Lol");
    gtk_box_pack_start(GTK_BOX(scrollable_box), user_nickname, FALSE, FALSE, 0);

    gtk_widget_show_all(GTK_WIDGET(user_settings_event_box));
}
