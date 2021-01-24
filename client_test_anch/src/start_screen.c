#include "Chat.h"

static void sing_in(GtkWidget *widget, GdkEventButton *event, gpointer *login[]) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)login[0])));
        printf("login: %s\n", name);
        gtk_entry_set_text(GTK_ENTRY(login[0]), "");
        char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)login[1])));
        printf("password: %s\n", passwrod);
        gtk_entry_set_text(GTK_ENTRY(login[1]), "");
    }
}


void start_screen(GtkWidget **activity_block) {
    
    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "resource/styles/sign_in.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.login_box), "login_box");
    gtk_fixed_put(GTK_FIXED(*activity_block), main_data.login_box, 100, 100);
    

    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(logo_box), "logo_box");
    gtk_box_pack_start(GTK_BOX(main_data.login_box), logo_box, FALSE, FALSE, 0);

    GtkWidget *Chat_logo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(Chat_logo), "Chat_logo");
    gtk_widget_set_size_request(GTK_WIDGET(Chat_logo), 200, 200);
    gtk_box_pack_start(GTK_BOX(logo_box), Chat_logo, FALSE, FALSE, 0);

    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.login_box), sing_in_data[0], FALSE, FALSE, 0);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.login_box), sing_in_data[1], FALSE, FALSE, 0);

    GtkWidget *enter_button = gtk_button_new_with_label ("Sign in");
    gtk_widget_set_name(GTK_WIDGET(enter_button), "enter_button");
    gtk_button_set_relief(GTK_BUTTON(enter_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(main_data.login_box), enter_button, FALSE, FALSE, 0);

    GtkWidget *registration_button = gtk_button_new_with_label ("Sign up");
    gtk_widget_set_name(GTK_WIDGET(registration_button), "registration_button");
    gtk_button_set_relief(GTK_BUTTON(registration_button), GTK_RELIEF_NONE);
    gtk_box_pack_end(GTK_BOX(main_data.login_box), registration_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(enter_button), "button_press_event", G_CALLBACK(sing_in), sing_in_data);
    g_signal_connect(G_OBJECT(registration_button), "button_press_event", G_CALLBACK(register_screen), (gpointer **)activity_block);

    gtk_widget_show_all(main_data.login_box);


}
