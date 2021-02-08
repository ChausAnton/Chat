#include "Chat.h"

void new_chat(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int size = atoi(message);

	db_add_chat(size, "New Chat", db);
	int last_chat = db_get_last_chat_id(db);

	message = clear_client_message(message);

	char **users_id = (char **) malloc(sizeof(char *) * size);
	for (int i = 1; i < size; i++) {
		recv(sock, message, 1000, 0);
		send(sock, "@GET", strlen("@GET"), 0);
		users_id[i] = strdup(message);
		db_add_member(last_chat, atoi(message));
		message = clear_client_message(message);
	}

	db_add_member(last_chat, db_get_user_id(user_name, db));

	send(sock, mx_itoa(last_chat), strlen(mx_itoa(last_chat)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);
}
