#include "Chat.h"

char *int_to_str(int num) {

   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}

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

void sign_in(GtkWidget *widget, GdkEventButton *event, gpointer *login[]) {

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

void sign_up(GtkWidget *widget, GdkEventButton *event, gpointer *sign_up[]) {

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
