#include "Chat.h"

void new_chat(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int size = atoi(message);

	while(server_access == false) {};
	server_access = false;
	db_add_chat(size, "New Chat", db);
	int last_chat = db_get_last_chat_id(db);
	server_access = true;
	
	message = clear_client_message(message);

	char **users_id = (char **) malloc(sizeof(char *) * size);
	for (int i = 1; i < size; i++) {
		recv(sock, message, 1000, 0);
		send(sock, "@GET", strlen("@GET"), 0);
		users_id[i] = strdup(message);

		while(server_access == false) {};
		server_access = false;
		db_add_member(last_chat, atoi(message));
		server_access = true;
		message = clear_client_message(message);

		while(server_access == false) {};
		server_access = false;
		char *login = db_get_user_login(atoi(users_id[i]), db);
		server_access = true;
		send(sock, login, strlen(login), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//user login

		while(server_access == false) {};
		server_access = false;
		message = db_get_user_name(login, db);
		server_access = true;
		send(sock, message, strlen(message), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//user name

		while(server_access == false) {};
		server_access = false;
		message = db_get_user_image_path(login, db);
		server_access = true;
		if (*message == '\0')
			message = strdup("resource/images/anonymous.png");

		send(sock, message, strlen(message), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//image path
	}

	while(server_access == false) {};
	server_access = false;
	db_add_member(last_chat, db_get_user_id(user_name, db));
	server_access = true;

	send(sock, mx_itoa(last_chat), strlen(mx_itoa(last_chat)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);
}
