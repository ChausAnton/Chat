#include "Chat.h"

void *scrolling_sticker() {

    usleep(3000);
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(messages_area_scroll));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    gtk_widget_show_all(main_data.main_box.right_chat_box);
    return NULL;
}

void emoji_click(GtkWidget *widget, GdkEventButton *event, gpointer *sticker_path) {

    if (widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1){
        GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
        gtk_box_pack_start(GTK_BOX(messanges_area_for_scroll), message_body, FALSE, FALSE, 0);

        GtkWidget *message_file = gtk_image_new();
        GdkPixbuf *message_file_pixbuf = gdk_pixbuf_new_from_file((gchar *)sticker_path, NULL);
        
        gint width = gdk_pixbuf_get_width(message_file_pixbuf);
        gint height = gdk_pixbuf_get_height(message_file_pixbuf);

        if (width > 52 || height > 52) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), gdk_pixbuf_new_from_file_at_scale((gchar *)sticker_path, 52, 52, TRUE, NULL));
        } else {
            gtk_image_set_from_pixbuf(GTK_IMAGE(message_file), message_file_pixbuf);
        }
        g_object_unref(G_OBJECT(message_file_pixbuf));

        gtk_box_pack_end(GTK_BOX(message_body), message_file, FALSE, FALSE, 0);

        pthread_t display_thread = NULL;
        pthread_create(&display_thread, NULL, scrolling_sticker, NULL);
    }
    gtk_widget_show_all(main_data.main_box.right_chat_box);
}

void show_emoji_box(GtkWidget *widget) {

    GtkWidget *emoji_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(emoji_event_box), "emoji_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(emoji_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(emoji_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(main_data.activity_block), emoji_event_box, 0, 0);

    GtkWidget *position_emoji_box = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(emoji_event_box), position_emoji_box);

    GtkWidget *emoji_event_box_for_click = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(emoji_event_box_for_click), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(position_emoji_box), emoji_event_box_for_click, 1125, 540);

    GtkWidget *emoji_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(emoji_box), "emoji_box");
    gtk_container_add(GTK_CONTAINER(emoji_event_box_for_click), emoji_box);

    GtkWidget *scrollable_emoji = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable_emoji), 185, 265);
    gtk_box_pack_start(GTK_BOX(emoji_box), scrollable_emoji, FALSE, FALSE, 0);

    GtkWidget *emoji_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(emoji_grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(emoji_grid), 10);

    int sticker_num = 1;
    GtkWidget *single_emoji;
    
    for(int i = 2; i <= 11; i++) {
        for(int j = 1; j <= 3; j++) {
            single_emoji = gtk_event_box_new();  
            //gtk_widget_set_name(GTK_WIDGET(single_emoji), "emoji");
            gtk_grid_attach(GTK_GRID(emoji_grid), single_emoji, j, i, 1, 1);

            GtkWidget *sticker_photo = gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_WIDGET(sticker_photo), 55, 55);
            char *path_sticker_photo = strdup("resource/images/stickers/");
            path_sticker_photo =  mx_strjoin(path_sticker_photo, int_to_str(sticker_num));
            path_sticker_photo =  mx_strjoin(path_sticker_photo, ".png");
            
            g_signal_connect(G_OBJECT(sticker_photo), "draw", G_CALLBACK(draw_sticker_photo), path_sticker_photo);
            gtk_container_add(GTK_CONTAINER(single_emoji), sticker_photo);

            g_signal_connect(G_OBJECT(single_emoji), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(single_emoji), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

            g_signal_connect(G_OBJECT(single_emoji), "button_press_event", G_CALLBACK(emoji_click), (void *)path_sticker_photo);

            sticker_num++;
            if(sticker_num > 20) break;
        }
        if(sticker_num > 20) break;
    }
    gtk_container_add(GTK_CONTAINER(scrollable_emoji), emoji_grid);

    gtk_widget_show_all(GTK_WIDGET(emoji_event_box));

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
}
