#pragma once 
#ifndef chat
#define chat
//ipconfig getifaddr en0 for get ip
//10.11.7.8 ansh
//10.11.7.7 anch
#define SERVERADDR "10.11.12.3"
#define SERVERPORT 8977

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

void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_itoa(int number);


#endif
