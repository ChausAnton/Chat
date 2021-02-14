#include "Chat.h"

void add_user_to_chat(int sock) {
    char *message = clear_client_message(NULL);
    recv(sock, message, 1000, 0);
    int user_id = atoi(message);
	send(sock, "@user_id", strlen("@user_id"), 0);
	message = clear_client_message(message);

    recv(sock, message, 1000, 0);
    while(server_access == false) {};
	server_access = false;
    char *login = db_get_user_login(user_id, db);
	server_access = true;
	send(sock, login, strlen(login), 0);
    message = clear_client_message(message);

    recv(sock, message, 1000, 0);
    while(server_access == false) {};
	server_access = false;
    char *user_name = db_get_user_name(login, db);
	server_access = true;
	send(sock, user_name, strlen(user_name), 0);
    message = clear_client_message(message);

    recv(sock, message, 1000, 0);
    while(server_access == false) {};
	server_access = false;
    char *image = db_get_user_image_path(login, db);
	server_access = true;
	send(sock, image, strlen(image), 0);
    message = clear_client_message(message);

    recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
    int chat_id = atoi(message);
    message = clear_client_message(message);

    while(server_access == false) {};
	server_access = false;
    db_add_member(chat_id, user_id);
    server_access = true;

     while(server_access == false) {};
	server_access = false;
    db_set_chat_count(chat_id, get_count_users_for_chat(chat_id, db))
    server_access = true;
    free(image);
    free(login);
}
