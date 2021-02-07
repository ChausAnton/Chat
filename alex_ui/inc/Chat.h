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
#include <math.h>
#include <netinet/in.h>

// Server
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Gtk
#include <gtk/gtk.h>

// Database
#include <sqlite3.h>

int new_chat_users_id[100];

enum chat_settings_message {RENAME_CHAT = 1, ADD_USER, DELETE_USER, DELETE_CHAT, CHANGE_CHAT_IMAGE};

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
    int* users_id;
    char* image_path;
    GtkWidget *chat_button;
}   t_chat_list;

typedef struct s_user {
    int user_id;
    char *login;
    char *password;
    char *name;
    char *image_path;
    t_chat_list *chat_array;
    int amount_of_chat;
}   t_user;

typedef struct s_main_box {
    GtkWidget *all_main_box;
    GtkWidget *main_fixed;
    GtkWidget *chat_bar;
    GtkWidget *right_chat_box;
    GtkWidget *messages_area_scroll;
    GtkWidget *messanges_area_for_scroll;
    GtkWidget *chat_bar_for_scroll;
    GtkWidget *chat_bar_scroll;
    GtkWidget *add_new_chat_event_box;
    GtkWidget *chat_settings_event_box;
    GtkWidget *user_settings_event_box;
    GtkWidget *up_box;
    GtkWidget *user_name_label;
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
void search_user_click(GtkWidget *widget);
void chat_settings_click(GtkWidget *widget, GdkEventButton *event, gpointer *data);
void sign_in();
void sign_up();
void logout(GtkWidget *widget, GdkEventButton *event);
void event_enter_notify_search(GtkWidget *widget);
void event_leave_notify_search(GtkWidget *widget);

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
void add_new_chat();

/* draw.c */
gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_chat_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_user_settings_avatar(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_sticker_photo(GtkWidget *widget, cairo_t *cr, char* path);

/* string.c */
char *mx_strjoin(const char *s1, const char *s2);
char *int_to_str(int num);
char *mx_strtrim(const char *str);

/* load_data.c */
void load_data_for_user();

/* load_chat_list.c */
void load_chat_list(); 

/* load_chat_box.c */
void load_right_chat_box();

/* chat_info.c */
void show_chat_info(GtkWidget *widget);

/* add_user.c */
void show_add_new_user(GtkWidget *widget);
void add_new_user();

#endif
