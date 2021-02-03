#include "Chat.h"

void emoji_click(GtkWidget *widget) {

    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    int emoji_id = atoi((char*)gtk_label_get_text(GTK_LABEL(parent->data)));
    printf("Emoji: %d\n", emoji_id);
}

void show_emoji_box(GtkWidget *widget) {

    GtkWidget *emoji_event_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(emoji_event_box), "emoji_event_box");
    gtk_widget_set_size_request(GTK_WIDGET(emoji_event_box), 1400, 900);
    g_signal_connect(G_OBJECT(emoji_event_box), "button_press_event", G_CALLBACK(unpress_event_box), widget);
    gtk_fixed_put(GTK_FIXED(activity_block), emoji_event_box, 0, 0);

    GtkWidget *position_emoji_box = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(emoji_event_box), position_emoji_box);

    GtkWidget *emoji_event_box_for_click = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(emoji_event_box_for_click), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(emoji_event_box_for_click), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(position_emoji_box), emoji_event_box_for_click, 1110, 545);

    GtkWidget *emoji_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(emoji_box), "emoji_box");
    gtk_container_add(GTK_CONTAINER(emoji_event_box_for_click), emoji_box);

    GtkWidget *scrollable_emoji = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable_emoji), 200, 260);
    gtk_box_pack_start(GTK_BOX(emoji_box), scrollable_emoji, FALSE, FALSE, 0);

    GtkWidget *emoji_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(emoji_grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(emoji_grid), 10);

    GtkWidget *emoji_label = gtk_label_new("Emoji");
    gtk_widget_set_name(GTK_WIDGET(emoji_label), "emoji_label");
    gtk_grid_attach(GTK_GRID(emoji_grid), emoji_label, 1, 0, 6, 1);

    int sticker_num = 1;
    GtkWidget *single_emoji;
    
    for(int i = 2; i <= 11; i++)    // Columns
    {
        for(int j = 1; j <= 6; j++) // Rows
        {
            //single_emoji = create_list(sticker_num);
            single_emoji = gtk_event_box_new();
            GtkWidget *key = gtk_label_new(int_to_str(sticker_num));
            gtk_widget_set_name(GTK_WIDGET(key), "hidden");
            gtk_container_add(GTK_CONTAINER(single_emoji), key);

            gtk_widget_set_size_request(GTK_WIDGET(single_emoji), 25, 25);
            gtk_grid_attach(GTK_GRID(emoji_grid), single_emoji, j, i, 1, 1);
            gtk_widget_set_name(GTK_WIDGET(single_emoji), "emoji");
            g_signal_connect(G_OBJECT(single_emoji), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(single_emoji), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
            g_signal_connect(G_OBJECT(single_emoji), "button_press_event", G_CALLBACK(emoji_click), NULL);
            sticker_num++;
            if(sticker_num > 82) break;
        }
    }
    gtk_container_add(GTK_CONTAINER(scrollable_emoji), emoji_grid);

    gtk_widget_show_all(GTK_WIDGET(emoji_event_box));

    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
}
