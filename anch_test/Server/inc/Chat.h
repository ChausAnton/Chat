#pragma once 
#ifndef chat
#define chat

#define SERVERPORT 8095

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
#include <sys/stat.h>

///server
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

////////gtk
#include <gtk/gtk.h>

///////database
#include <sqlite3.h>
#include <sys/stat.h>
/////

bool server_access;
///////
char *mx_autentification(int sock);
void *connection_handler(void *new_sock);
void file_work(int sock_from, int sock_to);

unsigned char * base64_encode(const unsigned char *src, size_t len,
			      size_t *out_len);


unsigned char * base64_decode(const unsigned char *src, size_t len,
			      size_t *out_len);

char *mx_itoa(int number);
void mx_printerr(const char *s);
void user_data_synchronization(int sock, char *user_name);
void new_chat(int sock, char *user_name);
void search_user(int sock, char *user_name);
void read_message(int sock);
void send_message(int sock, char *user_name);
////
char *mx_strnew(const int size);
int mx_strlen(const char *s);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strjoin(char const *s1, char const *s2);
char* int_to_str(int num);
char *mx_registration(int sock);
char *clear_client_message(char *str);
char **mx_strsplit(char const *s, char c);

/**Database**/
sqlite3* db;
void db_open(char* path, sqlite3** db);
void db_exec(char* statement, sqlite3* db);
void db_close(sqlite3* db);
void db_create();


char* db_get_user_name(char *login, sqlite3* db);
int db_get_count_user(sqlite3* db);

//User table
void db_add_user(char *login, char *password);
void db_del_user(char *login);
void db_set_user_password(char *login, char *new_pass);
void db_set_user_name(char *login, char *new_name);
void db_set_user_login(char *login, char *new_login);
char *db_get_user_password(char *login, sqlite3* db);
int db_get_user_id(char *login, sqlite3* db);
int db_get_count_user(sqlite3* db);
char* db_get_user_login(int user_id, sqlite3* db);
char* db_get_user_image_path(char *login, sqlite3* db);


//Online User table
void db_add_user_to_online(char *login, int socket, sqlite3* db);
void db_del_user_from_online(char *login, sqlite3* db);
int db_get_online_user_socket(char *login, sqlite3* db);
int db_get_count_online_user(sqlite3* db);


//Chats table
void db_add_chat(int count, char* name, sqlite3* db);
void db_del_chat(int chat_id, sqlite3* db);
int db_get_last_chat_id(sqlite3* db);
char* db_get_chat_name(int chat_id, sqlite3* db);
int get_count_users_for_chat(int chat_id, sqlite3* db);

//Messages table
void db_add_msg(int msg_id_in_chat, int chat_id, int user_id, char* date, char* text);
void db_del_all_msg_from_chat(int chat_id);
int db_get_count_msg_for_chat(int chat_id, sqlite3* db);
char** get_all_msg_for_chat(int chat_id, sqlite3* db);
char* get_msg_by_global_id(int msg_id, sqlite3* db) ;
char* get_msg_by_msg_id_and_chat_id(int msg_id_in_chat, int chat_id, sqlite3* db);
char** get_msg_for_chat_from_the_num(int msg_id_in_chat, int chat_id, sqlite3* db);
//Members table
void db_add_member(int chat_id, int user_id);
void db_del_member(int chat_id, int user_id);
void db_del_all_member_for_chat(int chat_id);
char** get_all_user_id_for_chat(int chat_id, sqlite3* db);
char** get_all_chat_id_for_user(int user_id, sqlite3* db); 
int get_count_chat_id_for_user(int user_id, sqlite3* db);

/**Database**/
#endif
