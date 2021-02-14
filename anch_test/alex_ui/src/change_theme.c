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
    //gtk_widget_set_name(GTK_WIDGET(clickable_change_theme), "clickable_change_theme");
    gtk_widget_set_halign(GTK_WIDGET(clickable_change_theme), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable_change_theme), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable_change_theme), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);

    gtk_fixed_put(GTK_FIXED(position_change_theme), clickable_change_theme, 580, 400);

    GtkWidget *change_theme_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_name(GTK_WIDGET(change_theme_box), "change_theme_box");
    gtk_container_add(GTK_CONTAINER(clickable_change_theme), change_theme_box);

    GtkWidget *change_theme_up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_name(GTK_WIDGET(change_theme_up_box), "change_theme_up_box");
    gtk_container_add(GTK_CONTAINER(change_theme_box), change_theme_up_box);

    GtkWidget *change_theme_label = gtk_label_new("Choose your theme:");
    gtk_widget_set_name(GTK_WIDGET(change_theme_label), "change_theme_label");
    gtk_box_pack_start(GTK_BOX(change_theme_up_box), change_theme_label, FALSE, FALSE, 0);

    GtkWidget *change_theme_down_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_name(GTK_WIDGET(change_theme_down_box), "change_theme_down_box");
    gtk_container_add(GTK_CONTAINER(change_theme_box), change_theme_down_box);

    //Default theme
    GtkWidget *default_theme_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(default_theme_event_box), "default_theme_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(default_theme_event_box), 100, 100);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(default_theme_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(change_theme_down_box), default_theme_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(default_theme_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(default_theme_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *default_theme_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(default_theme_box), "default_theme_box");
    gtk_widget_set_size_request(GTK_WIDGET(default_theme_box), 100, 100);
    gtk_container_add(GTK_CONTAINER(default_theme_event_box), default_theme_box);

    g_signal_connect(G_OBJECT(default_theme_event_box), "button_press_event", G_CALLBACK(change_theme_to_default), NULL);

    //Dark theme
    GtkWidget *dark_theme_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(dark_theme_event_box), "dark_theme_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(dark_theme_event_box), 100, 100);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(dark_theme_event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(change_theme_down_box), dark_theme_event_box, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(dark_theme_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify_search), NULL);
    g_signal_connect(G_OBJECT(dark_theme_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify_search), NULL);

    GtkWidget *dark_theme_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(dark_theme_box), "dark_theme_box");
    gtk_widget_set_size_request(GTK_WIDGET(dark_theme_box), 100, 100);
    gtk_container_add(GTK_CONTAINER(dark_theme_event_box), dark_theme_box);

    g_signal_connect(G_OBJECT(dark_theme_event_box), "button_press_event", G_CALLBACK(change_theme_to_dark), NULL);

    gtk_widget_show_all(GTK_WIDGET(main_data.main_box.change_theme_event_box));
}
