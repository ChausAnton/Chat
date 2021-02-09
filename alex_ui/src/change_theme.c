#include "Chat.h"

void show_change_theme(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);

    main_data.main_box.change_theme_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.change_theme_event_box), "change_theme_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.change_theme_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(main_data.main_box.change_theme_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.change_theme_event_box, 0, 0);

    GtkWidget *position_change_theme = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_data.main_box.change_theme_event_box), position_change_theme);

    GtkWidget *clickable_change_theme = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(clickable_change_theme), "clickable_change_theme");
    gtk_widget_set_halign(GTK_WIDGET(clickable_change_theme), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_change_theme), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_change_theme), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

    gtk_fixed_put(GTK_FIXED(position_change_theme), clickable_change_theme, 640, 120);

    GtkWidget *change_theme_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(change_theme_box), "change_theme_box");
    gtk_container_add(GTK_CONTAINER(clickable_change_theme), change_theme_box);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 230);
    gtk_box_pack_start(GTK_BOX(change_theme_box), scrollable, FALSE, FALSE, 0);

    GtkWidget *scrollable_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(scrollable_box), "scrollable_box");
    gtk_container_add(GTK_CONTAINER(scrollable), scrollable_box);

    //Default theme
    GtkWidget *default_theme_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(default_theme_event_box), "user_settings_photo_event_box");
    gtk_box_pack_start(GTK_BOX(scrollable_box), default_theme_event_box, FALSE, FALSE, 0);

    GtkWidget *default_theme_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(default_theme_avatar), 100, 100);
    char *default_path = strdup(user_data.image_path);
    g_signal_connect(G_OBJECT(default_theme_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), default_path);  

    GtkWidget *default_theme_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(default_theme_photo), "chat_info_photo");
    gtk_container_add(GTK_CONTAINER(default_theme_photo), default_theme_avatar);
    gtk_container_add(GTK_CONTAINER(default_theme_event_box), default_theme_photo);

    GtkWidget *default_theme_label = gtk_label_new("Default theme");
    gtk_label_set_selectable(GTK_LABEL(default_theme_label), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(default_theme_label), GTK_ALIGN_START);
    gtk_widget_set_name(GTK_WIDGET(default_theme_label), "new_chat_box_label");
    gtk_container_add(GTK_CONTAINER(default_theme_photo), default_theme_label);

    //g_signal_connect(G_OBJECT(default_theme_event_box), "button_press_event", G_CALLBACK(change_theme), NULL);

    //Dark theme
    GtkWidget *dark_theme_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(dark_theme_event_box), "user_settings_photo_event_box");
    gtk_box_pack_start(GTK_BOX(scrollable_box), dark_theme_event_box, FALSE, FALSE, 0);

    GtkWidget *dark_theme_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(dark_theme_avatar), 100, 100);
    char *dark_path = strdup(user_data.image_path);
    g_signal_connect(G_OBJECT(dark_theme_avatar), "draw", G_CALLBACK(draw_user_settings_avatar), dark_path);  

    GtkWidget *dark_theme_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(dark_theme_photo), "chat_info_photo");
    gtk_container_add(GTK_CONTAINER(dark_theme_photo), dark_theme_avatar);
    gtk_container_add(GTK_CONTAINER(dark_theme_event_box), dark_theme_photo);

    GtkWidget *dark_theme_label = gtk_label_new("Dark theme");
    gtk_label_set_selectable(GTK_LABEL(dark_theme_label), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(dark_theme_label), GTK_ALIGN_START);
    gtk_widget_set_name(GTK_WIDGET(dark_theme_label), "new_chat_box_label");
    gtk_container_add(GTK_CONTAINER(dark_theme_photo), dark_theme_label);

    //g_signal_connect(G_OBJECT(dark_theme_event_box), "button_press_event", G_CALLBACK(change_theme), NULL);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.change_theme_event_box));
}
