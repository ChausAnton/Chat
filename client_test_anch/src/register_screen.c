#include "Chat.h"

static void sign_up(GtkWidget *widget, GdkEventButton *event, gpointer *sign_up[]) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)sign_up[0])));
        printf("login: %s\n", name);
        gtk_entry_set_text(GTK_ENTRY(sign_up[0]), "");
        char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)sign_up[1])));
        printf("password: %s\n", passwrod);
        gtk_entry_set_text(GTK_ENTRY(sign_up[1]), "");
        char *repeat_passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)sign_up[2])));
        printf("repeat password: %s\n", repeat_passwrod);
        gtk_entry_set_text(GTK_ENTRY(sign_up[2]), "");
    }
}


void register_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl) {
    GtkWidget **activity_block = (GtkWidget **)activity_bl;
    gtk_widget_destroy(GTK_WIDGET(main_data.login_box));
    //gtk_widget_destroy(GTK_WIDGET(main_data.main_screen_box));
    if (widget) {}
    if(event->type != GDK_BUTTON_PRESS && event->button != 1){
        return;
    }

    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "resource/styles/sign_up.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.reg_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(main_data.reg_box), "reg_box");
    gtk_fixed_put(GTK_FIXED(*activity_block), main_data.reg_box, 100, 100);

    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(logo_box), "logo_box");
    gtk_box_pack_start(GTK_BOX(main_data.reg_box), logo_box, FALSE, FALSE, 0);

    GtkWidget *logo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(logo), "logo");
    gtk_widget_set_size_request(GTK_WIDGET(logo), 200, 200);
    gtk_box_pack_start(GTK_BOX(logo_box), logo, FALSE, FALSE, 0);

    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.reg_box), sing_in_data[0], FALSE, FALSE, 10);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.reg_box), sing_in_data[1], FALSE, FALSE, 10);

    sing_in_data[2] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[2]), "password_again");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[2]), "Repeat Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[2]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.reg_box), sing_in_data[2], FALSE, FALSE, 10);

    GtkWidget *register_button = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(GTK_WIDGET(register_button), "register_button");
    gtk_button_set_relief(GTK_BUTTON(register_button), GTK_RELIEF_NONE);
    gtk_box_pack_end(GTK_BOX(main_data.reg_box), register_button, FALSE, FALSE, 0);

    gtk_widget_show_all(main_data.reg_box);
    g_signal_connect(G_OBJECT(register_button), "button_press_event", G_CALLBACK(sign_up), sing_in_data);
}

