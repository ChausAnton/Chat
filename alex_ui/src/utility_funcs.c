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

void chat_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    children = children->next->next;
    int chat_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    printf("Chat_id: %d\n", chat_id);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
}

void sign_in() {
    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[0])));
    printf("login: %s\n", name);
    //gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[0]), "");
    char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.login_box.sign_in_data[1])));
    printf("password: %s\n", passwrod);
    //gtk_entry_set_text(GTK_ENTRY(main_data.login_box.sign_in_data[1]), "");

    if(TRUE) main_screen();
}

void sign_up() {
    char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[0])));
    printf("login: %s\n", name);
    //gtk_entry_set_text(GTK_ENTRY(sign_up[0]), "");
    char *passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[1])));
    printf("password: %s\n", passwrod);
    //gtk_entry_set_text(GTK_ENTRY(sign_up[1]), "");
    char *repeat_passwrod = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)main_data.reg_box.sign_up_data[2])));
    printf("repeat password: %s\n", repeat_passwrod);
    //gtk_entry_set_text(GTK_ENTRY(sign_up[2]), "");

    if(TRUE) main_screen();
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

        GtkWidget *logout_label = gtk_label_new("Are you sure????");
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
