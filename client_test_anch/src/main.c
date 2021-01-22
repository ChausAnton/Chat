#include "Chat.h"


void entry_text_change_event(GtkWidget *widget, GdkEventButton *event, gpointer search_field) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)search_field)));
        printf("%s\n", name);
    }
}

void sing_in(GtkWidget *widget, GdkEventButton *event, gpointer *login[]) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)login[0])));
        printf("login: %s\n", name);
        gtk_entry_set_text(GTK_ENTRY(login[0]), "");
        char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)login[1])));
        printf("passwrod: %s\n", passwrod);
        gtk_entry_set_text(GTK_ENTRY(login[1]), "");
    }
}

/*void sing_in_password(GtkWidget *widget, GdkEventButton *event, gpointer passwod) {
    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)passwod)));
        printf("%s\n", name);
        gtk_entry_set_text(GTK_ENTRY(passwod), "");
    }
}*/



int main(int argc, char *argv[]) {
    GtkWidget *window;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 900);

    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(activity), "activity");                       // Имя
    gtk_container_add(GTK_CONTAINER(window), activity);

    GtkWidget *activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), 1400, 900);   // Размер
    gtk_container_add(GTK_CONTAINER(activity), activity_block);            // Позиция

      

    GtkWidget *line = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(line), "line");
    gtk_widget_set_size_request(GTK_WIDGET(line), 100, 900);
    gtk_fixed_put(GTK_FIXED(activity_block), line, 300, 0);

    GtkWidget *enter_button = gtk_button_new_with_label ("Enter");
    gtk_widget_set_name(GTK_WIDGET(enter_button), "enter_button");
    gtk_button_set_relief(GTK_BUTTON(enter_button), GTK_RELIEF_NONE);
    gtk_fixed_put(GTK_FIXED(activity_block), enter_button, 800, 750);

//////////////
   /* GtkWidget *entry_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(entry_block), "entry_block");
    gtk_widget_set_size_request(GTK_WIDGET(entry_block), 100, 30);
    gtk_fixed_put(GTK_FIXED(activity_block),entry_block, 700, 450);*/
    GtkWidget *sing_in_data[2];
    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 1000);
    gtk_fixed_put(GTK_FIXED(activity_block), sing_in_data[0], 700, 450);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 1000);
    gtk_fixed_put(GTK_FIXED(activity_block), sing_in_data[1], 700, 500);

    g_signal_connect(G_OBJECT(enter_button), "button_press_event", G_CALLBACK(sing_in), sing_in_data);
    //g_signal_connect(G_OBJECT(button), "button_press_event", G_CALLBACK(sing_in_password), sing_in[1]);

//////////////

    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //g_signal_connect(button, "button_press_event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
