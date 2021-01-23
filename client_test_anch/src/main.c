#include "Chat.h"


void sing_in(GtkWidget *widget, GdkEventButton *event, gpointer *login[]) {
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
    GtkWidget *login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(login_box), "login_box");
    gtk_widget_set_size_request(GTK_WIDGET(login_box), 380, 530);
    gtk_fixed_put(GTK_FIXED(*activity_block), login_box, 100, 100);
    

    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(logo_box), "logo_box");
    //gtk_fixed_put(GTK_FIXED(*activity_block), logo_box, 130, 110);
    gtk_box_pack_start(GTK_BOX(login_box), logo_box, FALSE, FALSE, 0);

    GtkWidget *Chat_logo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(Chat_logo), "Chat_logo");
    gtk_widget_set_size_request(GTK_WIDGET(Chat_logo), 200, 200);
    //gtk_fixed_put(GTK_FIXED(*activity_block), Chat_logo, 160, 540);
    gtk_box_pack_start(GTK_BOX(logo_box), Chat_logo, FALSE, FALSE, 0);

    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 30);
    //gtk_fixed_put(GTK_FIXED(*activity_block), sing_in_data[0], 160, 350);
    gtk_box_pack_start(GTK_BOX(login_box), sing_in_data[0], FALSE, FALSE, 0);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 30);
    //gtk_fixed_put(GTK_FIXED(*activity_block), sing_in_data[1], 160, 400);
    gtk_box_pack_start(GTK_BOX(login_box), sing_in_data[1], FALSE, FALSE, 0);

    GtkWidget *enter_button = gtk_button_new_with_label ("Sign in");
    gtk_widget_set_name(GTK_WIDGET(enter_button), "enter_button");
    gtk_button_set_relief(GTK_BUTTON(enter_button), GTK_RELIEF_NONE);
    //gtk_fixed_put(GTK_FIXED(*activity_block), enter_button, 160, 480);
    gtk_box_pack_start(GTK_BOX(login_box), enter_button, FALSE, FALSE, 0);

    GtkWidget *registration_button = gtk_button_new_with_label ("Sign up");
    gtk_widget_set_name(GTK_WIDGET(registration_button), "registration_button");
    gtk_button_set_relief(GTK_BUTTON(registration_button), GTK_RELIEF_NONE);
    //gtk_fixed_put(GTK_FIXED(*activity_block), registration_button, 160, 540);
    gtk_box_pack_end(GTK_BOX(login_box), registration_button, FALSE, FALSE, 0);


    g_signal_connect(G_OBJECT(enter_button), "button_press_event", G_CALLBACK(sing_in), sing_in_data);

    //g_signal_connect(G_OBJECT(enter_button), "button_press_event", G_CALLBACK(sing_in), sing_in_data);
   
}


int main(int argc, char *argv[]) {
    GtkWidget *window;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), window_size_x, window_size_y);

    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "resource/styles/sign_in.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(activity), "activity");
    gtk_container_add(GTK_CONTAINER(window), activity);

    GtkWidget *activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), window_size_x, window_size_y);
    gtk_container_add(GTK_CONTAINER(activity), activity_block);
    
    start_screen(&activity_block);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
