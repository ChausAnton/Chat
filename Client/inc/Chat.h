#pragma once 
#ifndef chat
#define chat
//ipconfig getifaddr en0 for get ip
//10.11.7.8 ansh
//10.11.7.7 anch
#define SERVERADDR "10.11.7.7"
#define SERVERPORT 8339

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

char *mx_itoa(int number);

unsigned char * base64_encode(const unsigned char *src, size_t len,
			      size_t *out_len);


unsigned char * base64_decode(const unsigned char *src, size_t len,
			      size_t *out_len);

char *mx_strjoin(char const *s1, char const *s2);

char **mx_strsplit(char const *s, char c);

int mx_get_char_index(const char *str, char c);

#endif
