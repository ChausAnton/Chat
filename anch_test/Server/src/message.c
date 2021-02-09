#include "Chat.h"

void read_message(int sock, int chat_id) {
	char *message = clear_client_message(NULL);

	int count = db_get_count_msg_for_chat(chat_id, db);

	send(sock, mx_itoa(count), strlen(mx_itoa(count)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);

	int count_user = atoi(message);
	message = clear_client_message(message);
	char **messages = get_msg_for_chat_from_the_num(count_user, chat_id, db);//from to 

	mx_printerr(mx_itoa(count_user));
	mx_printerr(" \n ");
	mx_printerr(mx_itoa(count));

	for(int i = 0; i < (count-count_user); i++) {
		int size = strlen(messages[i]);

		send(sock, mx_itoa(size), strlen(mx_itoa(size)), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);

		send(sock, messages[i], strlen(messages[i]), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);
	}
}

