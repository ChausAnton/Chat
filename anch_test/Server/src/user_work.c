#include "Chat.h"

void save_user_changes(int sock) {
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
    char *login = strdup(message);
	send(sock, "@login", strlen("@login"), 0);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
    char *new_name = strdup(message);
	send(sock, "@new_name", strlen("@new_name"), 0);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	db_set_user_name(login, new_name);
	server_access = true;
}


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
    if (*image == '\0')
			image = strdup("resource/images/anonymous.png");
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
    db_set_chat_count(chat_id, get_count_users_for_chat(chat_id, db) + 1);
    server_access = true;
    free(image);
    free(login);
}

void read_new_user(int sock) {
    char *message = clear_client_message(NULL);
    recv(sock, message, 1000, 0);
    int chat_id = atoi(message);

	send(sock, "@chat_id", strlen("@chat_id"), 0);
	message = clear_client_message(message);

    while(server_access == false) {};
	server_access = false;
    char **all_user_id = get_all_user_id_for_chat(chat_id, db);
    server_access = true;

    int size = 0;
    while(all_user_id[size] != NULL) 
        size++;

    recv(sock, message, 1000, 0);
	send(sock, mx_itoa(size), strlen(mx_itoa(size)), 0);
	message = clear_client_message(message);

    for(int i = 0; i < size; i++) {

        recv(sock, message, 1000, 0);
	    send(sock, all_user_id[i], strlen(all_user_id[i]), 0);
	    message = clear_client_message(message);

        recv(sock, message, 1000, 0);
        while(server_access == false) {};
	    server_access = false;
        char *login = db_get_user_login(atoi(all_user_id[i]), db);
        server_access = true;
	    send(sock, login, strlen(login), 0);
	    message = clear_client_message(message);

        recv(sock, message, 1000, 0);
        while(server_access == false) {};
	    server_access = false;
        char *name = db_get_user_name(login, db);
        server_access = true;
	    send(sock, name, strlen(name), 0);
	    message = clear_client_message(message);

        recv(sock, message, 1000, 0);
        while(server_access == false) {};
	    server_access = false;
        char *image_path = db_get_user_image_path(login, db);
        if (*image_path == '\0')
			image_path = strdup("resource/images/anonymous.png");
        server_access = true;
	    send(sock, image_path, strlen(image_path), 0);
	    message = clear_client_message(message);

        free(image_path);
        free(name);
        free(login);
    }

}
