#include "Chat.h"

GtkWidget *sing_in_data[3];


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

void start_screen(GtkWidget **activity_block) {
    GtkWidget *enter_button = gtk_button_new_with_label ("Enter");
    gtk_widget_set_name(GTK_WIDGET(enter_button), "enter_button");
    gtk_button_set_relief(GTK_BUTTON(enter_button), GTK_RELIEF_NONE);
    gtk_fixed_put(GTK_FIXED(*activity_block), enter_button, 800, 750);


    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 1000);
    gtk_fixed_put(GTK_FIXED(*activity_block), sing_in_data[0], 700, 450);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 1000);
    gtk_fixed_put(GTK_FIXED(*activity_block), sing_in_data[1], 700, 500);

    g_signal_connect(G_OBJECT(enter_button), "button_press_event", G_CALLBACK(sign_in), sing_in_data);
   
}

void register_screen(GtkWidget **activity_block) {
    GtkWidget *reg_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(reg_box), "reg_box");
    //gtk_widget_set_size_request(GTK_WIDGET(reg_box), 10, 10);
    gtk_fixed_put(GTK_FIXED(*activity_block), reg_box, 100, 100);
    
    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, 10, 10, 10, 10); 
    //GtkAdjustment *hadjustment = gtk_adjustment_new(0, 0, 0, 0, 0, 0); 
    GtkWidget *scrolled_message =  gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(GTK_WIDGET(scrolled_message), "scrollable_msg");
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_message), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    //gtk_scrolled_window_set_max_content_width(GTK_SCROLLED_WINDOW(scrolled_message), 10);
    //gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW(scrolled_message), 10);
    //gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_message), 30.0f);
    //gtk_scrolled_window_set_kinetic_scrolling (GTK_SCROLLED_WINDOW(scrolled_message), TRUE);
    //gtk_scrolled_window_set_placement(GTK_SCROLLED_WINDOW(scrolled_message),  GTK_CORNER_TOP_RIGHT);
    //gtk_widget_set_size_request(scrolled_message, 100, 30); 

    GtkWidget *view = gtk_text_view_new();
    //GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
    //gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1); 
    gtk_widget_set_name(GTK_WIDGET(view), "view");
    gtk_container_add(GTK_CONTAINER(scrolled_message), view);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(view), GTK_WRAP_WORD_CHAR);
    //gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(view), GTK_TEXT_WINDOW_TOP, 10);
    gtk_box_pack_start(GTK_BOX(reg_box), scrolled_message, FALSE, FALSE, 10);         
    //gtk_fixed_put(GTK_FIXED(main),scrolled_message, LIST_W, 0);  
    //gtk_container_add (GTK_CONTAINER (view), GTK_WIDGET(scrolled_window));
    //gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 30);
    //gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW (view), GTK_TEXT_MARK(view));


    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(logo_box), "logo_box");
    //gtk_widget_set_size_request(GTK_WIDGET(logo_box), 10, 10);
    gtk_box_pack_start(GTK_BOX(reg_box), logo_box, FALSE, FALSE, 10);

    GtkWidget *logo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(logo), "logo");
    gtk_widget_set_size_request(GTK_WIDGET(logo), 200, 200);
    gtk_box_pack_start(GTK_BOX(logo_box), logo, FALSE, FALSE, 10);

    sing_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[0]), "login");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[0]), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[0]), 30);
    gtk_box_pack_start(GTK_BOX(reg_box), sing_in_data[0], FALSE, FALSE, 10);

    sing_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[1]), "password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[1]), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[1]), 30);
    gtk_box_pack_start(GTK_BOX(reg_box), sing_in_data[1], FALSE, FALSE, 10);

    sing_in_data[2] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(sing_in_data[2]), "password_again");
    gtk_entry_set_placeholder_text(GTK_ENTRY(sing_in_data[2]), "Repeat Password:");
    gtk_entry_set_max_length(GTK_ENTRY(sing_in_data[2]), 30);
    gtk_box_pack_start(GTK_BOX(reg_box), sing_in_data[2], FALSE, FALSE, 10);

    /*GtkWidget *check_button = gtk_check_button_new_with_label("I accept");
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_button), FALSE);
    gtk_widget_set_name(GTK_WIDGET(check_button), "check_button");
    gtk_fixed_put(GTK_FIXED(*activity_block), check_button, 175, 395);
    
    //g_signal_connect (GTK_TOGGLE_BUTTON(check_button), "toggled", G_CALLBACK(print_bruh), NULL);

    GtkWidget *privat_policy = gtk_link_button_new_with_label ("https://github.com/ChausAnton/Chat", "Privat Policy");
    gtk_widget_set_name(GTK_WIDGET(privat_policy), "privat_policy");
    //gtk_button_set_relief(GTK_BUTTON(privat_policy), GTK_RELIEF_NONE);
    gtk_fixed_put(GTK_FIXED(*activity_block), privat_policy, 237, 388);*/

    GtkWidget *register_button = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(GTK_WIDGET(register_button), "register_button");
    gtk_button_set_relief(GTK_BUTTON(register_button), GTK_RELIEF_NONE);
    gtk_box_pack_end(GTK_BOX(reg_box), register_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(register_button), "button_press_event", G_CALLBACK(sign_up), sing_in_data);
}

void chat_screen(GtkWidget **activity_block, int num){
    GtkWidget *chats[num];

    GtkWidget *chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_box), "chat_box");

    GtkWidget *chat_box_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    GtkWidget *scrolled_chats = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_chats), chat_box_for_scroll); 
    gtk_widget_set_size_request(GTK_WIDGET(scrolled_chats), 350, 600);
    //gtk_box_pack_start(GTK_BOX(chat_box), scrolled_chats, TRUE, TRUE, 0);   

    for(int i = 0; i < num; i++) {
        GtkWidget *chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_button), "chat_button");
        //gtk_button_set_relief(GTK_BUTTON(chat_button), GTK_RELIEF_NONE);
        //gtk_event_box_set_visible_window(GTK_EVENT_BOX(chat_button), TRUE);

        GtkWidget* photo_chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(photo_chat), "chat_photo");
        gtk_widget_set_size_request(GTK_WIDGET(photo_chat), 70, 30);

        GtkWidget* name_chat = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(name_chat), "chat_name");

        chats[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chats[i]), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(chats[i]), 30, 30);
        gtk_box_pack_start(GTK_BOX(chats[i]), photo_chat, FALSE, FALSE, 10);
        gtk_box_pack_start(GTK_BOX(chats[i]), name_chat, FALSE, FALSE, 10);
        gtk_container_add(GTK_CONTAINER(chat_button), chats[i]); 
        gtk_box_pack_start(GTK_BOX(chat_box_for_scroll), chat_button, FALSE, FALSE, 0);
    }
    gtk_container_add(GTK_CONTAINER(chat_box), scrolled_chats); 
    gtk_fixed_put(GTK_FIXED(*activity_block), chat_box, 500, 200);

}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 900);

    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "sign up.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(activity), "activity");                 // Имя
    gtk_container_add(GTK_CONTAINER(window), activity);

    GtkWidget *activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), 1400, 900);   // Размер
    gtk_container_add(GTK_CONTAINER(activity), activity_block);            // Позиция

//////////////

    register_screen(&activity_block);
    chat_screen(&activity_block, 10);

//////////////

    /*GtkWidget *check_button = gtk_check_button_new_with_label("I accept");
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_button), FALSE);
    gtk_widget_set_name(GTK_WIDGET(check_button), "check_button");
    //gtk_widget_set_size_request(GTK_WIDGET(check_button), 10, 10);
    gtk_fixed_put(GTK_FIXED(activity_block), check_button, 800, 750);
    g_signal_connect (GTK_TOGGLE_BUTTON(check_button), "toggled", G_CALLBACK(print_bruh), NULL);*/

    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
