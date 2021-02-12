#include "Chat.h"

void search_user(int sock, char *user_name) {
	char *message = clear_client_message(NULL);
	user_name = clear_client_message(NULL);
	recv(sock, user_name, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);

	while(server_access == false) {};
	server_access = false;
	message = db_get_user_name(user_name, db);
	server_access = true;
	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	int user_id = db_get_user_id(user_name, db);
	server_access = true;

	send(sock, mx_itoa(user_id), strlen(mx_itoa(user_id)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);
}
