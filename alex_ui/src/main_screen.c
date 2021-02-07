#include "Chat.h"

void main_screen() {
  
    gtk_widget_destroy(GTK_WIDGET(main_data.activity_block));
    
    gtk_css_provider_load_from_path(main_data.styles, "resource/styles/main_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    
    main_data.main_box.all_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.all_main_box), "main_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.all_main_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), main_data.main_box.all_main_box, 0, 0);

    // Gtk fixed
    main_data.main_box.main_fixed = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.main_fixed), 300, 100);
    gtk_container_add(GTK_CONTAINER(main_data.main_box.all_main_box), main_data.main_box.main_fixed);
    
    // Chat bar
    main_data.main_box.chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.chat_bar, 0, 0);

        // Up box
        main_screen_up_box();

        // Chat list
        load_chat_list();

    for(int i =0; i < 100; i++){
        new_chat_users_id[i] = -1;
    }

    // Chat box
    main_data.main_box.right_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_box.right_chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_box.right_chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_data.main_box.main_fixed), main_data.main_box.right_chat_box, 310, 0);

    if(main_data.main_box.search_chat_id == -1) {
        GtkWidget *right_mid_box = gtk_label_new("Whom you want to write?");
        gtk_widget_set_name(GTK_WIDGET(right_mid_box), "right_mid_box");
        gtk_widget_set_size_request(GTK_WIDGET(right_mid_box), 240, 40);
        gtk_box_pack_start(GTK_BOX(main_data.main_box.right_chat_box), right_mid_box, TRUE, FALSE, 0);
    }

    gtk_widget_show_all(main_data.activity_block);
}
