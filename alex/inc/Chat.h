#pragma once 
#ifndef chat
#define chat
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

///server
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>


////////gtk
#include <gtk/gtk.h>

///////database
#include <sqlite3.h>


GtkWidget *sing_in_data[3];


typedef struct s_main_data {
    GtkWidget *login_box;
    GtkWidget *reg_box;
    GtkWidget *main_screen_box;
}   t_main_data;
t_main_data main_data;

void register_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl);
void start_screen(GtkWidget **activity_block);
void main_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_bl);

#endif
