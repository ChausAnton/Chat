#include "Chat.h"

void start_screen() {
    
    gtk_widget_destroy(GTK_WIDGET(main_data.activity_block));

    gtk_css_provider_load_from_path(main_data.styles, "resource/styles/sign_in.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    
    main_data.login_box.all_login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.login_box.all_login_box), "login_box");
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.login_box.all_login_box, 208, 0);

    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(logo_box), "logo_box");
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), logo_box, FALSE, FALSE, 0);

    GtkWidget *chat_logo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_logo), "chat_logo");
    gtk_widget_set_size_request(GTK_WIDGET(chat_logo), 200, 200);
    gtk_box_pack_start(GTK_BOX(logo_box), chat_logo, FALSE, FALSE, 0);

    GtkWidget *login_label = gtk_label_new("Login");
    gtk_widget_set_name(GTK_WIDGET(login_label), "login_label");
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), login_label, FALSE, FALSE, 0);

    main_data.login_box.sign_in_data[0] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.login_box.sign_in_data[0]), "login");
    gtk_entry_set_max_length(GTK_ENTRY(main_data.login_box.sign_in_data[0]), 30);
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), main_data.login_box.sign_in_data[0], FALSE, FALSE, 0);

    GtkWidget *password_label = gtk_label_new("Password");
    gtk_widget_set_name(GTK_WIDGET(password_label), "password_label");
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), password_label, FALSE, FALSE, 0);

    main_data.login_box.sign_in_data[1] = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.login_box.sign_in_data[1]), "password");
    gtk_entry_set_visibility(GTK_ENTRY(main_data.login_box.sign_in_data[1]), FALSE);
    gtk_entry_set_max_length(GTK_ENTRY(main_data.login_box.sign_in_data[1]), 28);
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), main_data.login_box.sign_in_data[1], FALSE, FALSE, 0);

    GtkWidget *signin_button = gtk_button_new_with_label ("Sign in");
    gtk_widget_set_name(GTK_WIDGET(signin_button), "signin_button");
    gtk_button_set_relief(GTK_BUTTON(signin_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), signin_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(signin_button), "button_press_event", G_CALLBACK(sign_in), main_data.login_box.sign_in_data);

    GtkWidget *signup_button = gtk_button_new_with_label ("Sign up");
    gtk_widget_set_name(GTK_WIDGET(signup_button), "signup_button");
    gtk_button_set_relief(GTK_BUTTON(signup_button), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(main_data.login_box.all_login_box), signup_button, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(signup_button), "button_press_event", G_CALLBACK(register_screen), NULL);
    
    gtk_widget_show_all(main_data.activity_block);
    gtk_widget_show_all(main_data.login_box.all_login_box);
}
