#include "Chat.h"

void test() {
    printf("!!!!!!!!");
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

    GtkWidget *up_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(up_box), "up_box");
    gtk_widget_set_size_request(GTK_WIDGET(up_box), 300, 100);
    gtk_fixed_put(GTK_FIXED(main_fixed), up_box, 3, 3);

    ///////////////
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(left_box), "left_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_box), window_size_x - 315, window_size_y - 6);
    gtk_fixed_put(GTK_FIXED(main_fixed), left_box, 310, 3);

    GtkWidget *left_mid_box =     gtk_label_new("Who you want to write ?");
    gtk_widget_set_name(GTK_WIDGET(left_mid_box), "left_mid_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_mid_box), 200, 30);
    gtk_fixed_put(GTK_FIXED(main_fixed), left_mid_box, 698, 420);
//////////////

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
