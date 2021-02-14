#include "Chat.h"

void save_edit_chat_changes(int sock) {
    char *message = clear_client_message(NULL);
    recv(sock, message, 1000, 0);
    int chat_id = atoi(message);
	send(sock, "@chat_id", strlen("@chat_id"), 0);
	message = clear_client_message(message);
    recv(sock, message, 1000, 0);
	send(sock, "@chat_name", strlen("@chat_name"), 0);

    while(server_access == false) {};
	server_access = false;
	db_set_chat_name(chat_id, message, db);
	server_access = true;
    free(message);
}

void send_edit_chat_changes(int sock) {
    char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@user_id", strlen("@user_id"), 0);
	int user_id = atoi(message);
	message = clear_client_message(message);

    while(server_access == false) {};
	server_access = false;
	char **all_chat_id = get_all_chat_id_for_user(user_id, db);
	server_access = true;
	int server_chat_num = 0;
	while(all_chat_id[server_chat_num] != NULL)
	server_chat_num++;

	recv(sock, message, 1000, 0);
	int user_chats_num = atoi(message);
	send(sock, "@GET", strlen("@GET"), 0);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	send(sock, mx_itoa(server_chat_num), strlen(mx_itoa(server_chat_num)), 0);
	message = clear_client_message(message);

    if(server_chat_num == user_chats_num) {
        for(int i = 0; i < server_chat_num; i++) {
			recv(sock, message, 1000, 0);
			send(sock, all_chat_id[i], strlen(all_chat_id[i]), 0);
			message = clear_client_message(message);

            recv(sock, message, 1000, 0);
      		while(server_access == false) {};
            server_access = false;
            char *chat_name = db_get_chat_name(atoi(all_chat_id[i]), db);
            server_access = true;
            send(sock, chat_name, strlen(chat_name), 0);
            message = clear_client_message(message);
            free(chat_name);
        }
    }
}


