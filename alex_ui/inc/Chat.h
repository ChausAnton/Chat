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
GtkWidget *messages_area_scroll;
GtkWidget *messanges_area_for_scroll;

typedef struct s_login_box {
    GtkWidget *all_login_box;
    GtkWidget *sign_in_data[2];
}   t_login_box;

typedef struct s_reg_box {
    GtkWidget *all_reg_box;
    GtkWidget *sign_up_data[3];
}   t_reg_box;

typedef struct s_chat_list {
    int chat_id;
    char* chat_name;
    int count_users;
    char** users_id;
    char* image_path;
}   t_chat_list;

typedef struct s_user {
    int user_id;
    char *login;
    char *password;
    t_chat_list *chat_array;
}   t_user;

typedef struct s_main_box {
    GtkWidget *all_main_box;
    GtkWidget *chat_bar;
    GtkWidget *right_chat_box;
    int search_chat_id;
}   t_main_box;


typedef struct s_main_data {
    GtkWidget *window;
    GtkWidget *activity;
    GtkWidget *activity_block;
    GtkCssProvider *styles;
    t_login_box login_box;
    t_reg_box reg_box;
    t_main_box main_box;
}   t_main_data;

t_main_data main_data;
t_user user_data;

void start_screen();
void register_screen();
void main_screen();

/* message_stuff.c */
void *scrolling_msg();
void display_message(char *message_text);
void send_message(GtkWidget *widget, GdkEventButton *event, gpointer *messsage);
void send_message_file(GtkWidget *widget, GdkEventButton *event, gpointer *messsage);

/* utility_funcs.c */
void event_enter_notify(GtkWidget *widget);
void event_leave_notify(GtkWidget *widget);
void unpress_event_box(GtkWidget *widget, GdkEventButton *event, gpointer *p);
void chat_click(GtkWidget *widget);
void sign_in();
void sign_up();
void logout(GtkWidget *widget, GdkEventButton *event);

/* emotes.c */
void *scrolling_sticker();
void show_emoji_box(GtkWidget *widget);
void emoji_click(GtkWidget *widget, GdkEventButton *event, gpointer *sticker_path);

/* chat_settings.c */
void show_chat_settings(GtkWidget *widget);

/* user_settings.c */
void show_user_settings(GtkWidget *widget);

/* add_new_chat.c */
void show_add_new_chat(GtkWidget *widget);

/* draw.c */
gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_chat_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_user_settings_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_sticker_photo(GtkWidget *widget, cairo_t *cr, char* path);

/* string.c */
char *mx_strjoin(const char *s1, const char *s2);
char *int_to_str(int num);

/* load_data.c */
void load_data_for_user();

/* load_chat_list.c */
void load_chat_list(); 
#endif
