#pragma once 
#ifndef CHAT_H
#define CHAT_H

//ipconfig getifaddr en0 for get ip
//10.11.7.8 ansh
//10.11.7.7 anch
#define SERVERADDR "10.11.7.7"
#define SERVERPORT 8696

#define WINDOW_SIZE_Y 900
#define WINDOW_SIZE_X 1400

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <math.h>

// Server
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>

// Gtk
#include <gtk/gtk.h>

// Database
#include <sqlite3.h>

GtkWidget *messanges_area_for_scroll;
GtkWidget *window;
GtkWidget *activity_block;
GtkWidget *sign_in_data[3];
GtkWidget *chat_box;

typedef struct s_main_data {
    GtkWidget *login_box;
    GtkWidget *reg_box;
    GtkWidget *main_screen_box;
}   t_main_data;
t_main_data main_data;

void start_screen(GtkWidget **activity_block);
void register_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl);
void main_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl);

/* message_stuff.c */
void display_message(char *message_text);
void send_message(GtkWidget *widget, GdkEventButton *event, gpointer *messsage);
void send_messege_file(GtkWidget *widget, GdkEventButton *event, gpointer *messsage);

/* utility_funcs.c */
char *int_to_str(int num);
void event_enter_notify(GtkWidget *widget);
void event_leave_notify(GtkWidget *widget);
void unpress_event_box(GtkWidget *widget, GdkEventButton *event, gpointer *p);
void chat_click(GtkWidget *widget);
void sign_in(GtkWidget *widget, GdkEventButton *event, gpointer *login[]);
void sign_up(GtkWidget *widget, GdkEventButton *event, gpointer *sign_up[]);

/* emotes.c */
void show_emoji_box(GtkWidget *widget);
void emoji_click(GtkWidget *widget);

/* chat_settings.c */
void show_chat_settings(GtkWidget *widget);

/* user_settings.c */
void show_user_settings(GtkWidget *widget);

gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_chat_avatar(GtkWidget *widget, cairo_t *cr, char* path);

#endif
