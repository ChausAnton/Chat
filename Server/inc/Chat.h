#pragma once 
#ifndef chat
#define chat

#define SERVERPORT 8696

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
/////


///////
char *mx_autentification(int sock);
void *connection_handler(void *new_sock);

////
char *mx_strnew(const int size);
int mx_strlen(const char *s);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strjoin(char const *s1, char const *s2);
char* int_to_str(int num);
void mx_registration(int sock);
//void clear_client_message(char *str);

/**Database**/
sqlite3* db;
void db_open(char* path, sqlite3** db);
void db_exec(char* statement, sqlite3* db);

//User table
void db_add_user(char *login, char *password);
void db_del_user(char *login);
void db_set_user_password(char *login, char *new_pass);
void db_set_user_name(char *login, char *new_name);
void db_set_user_login(char *login, char *new_login);
char *db_get_user_password(char *login, sqlite3* db);
int db_get_user_id(char *login, sqlite3* db);
int db_get_count_user(sqlite3* db);

//Online User table
void db_add_user_to_online(char *login, int socket, sqlite3* db);
void db_del_user_from_online(char *login, sqlite3* db);
int db_get_online_user_socket(char *login, sqlite3* db);
int db_get_count_online_user(sqlite3* db);
/**Database**/
#endif
