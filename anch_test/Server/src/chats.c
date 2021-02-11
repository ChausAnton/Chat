#include "Chat.h"

void read_message(int sock) {
	
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int chat_id = atoi(message);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	int user_num = atoi(message);
	message = clear_client_message(message);

	int server_num = db_get_count_msg_for_chat(chat_id, db);
	send(sock, mx_itoa(server_num), strlen(mx_itoa(server_num)), 0);
	message = clear_client_message(message);

	int messages_num = user_num - server_num;
	if (messages_num < 0) {
		messages_num = messages_num * -1;
	}
	char **messages = get_msg_for_chat_from_the_num(user_num, chat_id, db);//from to 
	for(int i = 0; i < messages_num; i++) {
		int size = strlen(messages[i]);

		recv(sock, message, 1000, 0);
		send(sock, mx_itoa(size), strlen(mx_itoa(size)), 0);
		message = clear_client_message(message);

		recv(sock, message, 1000, 0);
		send(sock, messages[i], strlen(messages[i]), 0);
		message = clear_client_message(message);

		mx_printerr(messages[i]);
	    mx_printerr("\n");
	}
}


char **chat_chose(int sock, int *chat_id) {
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	*chat_id = atoi(message);
	message = clear_client_message(message);

	char **chat_chose_users_id = get_all_user_id_for_chat(*chat_id, db);
	return chat_chose_users_id;
	mx_printerr(mx_itoa(*chat_id));
}


void send_message(int sock, int chat_id, char *user_name) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	char *text = strdup(message);
	message = clear_client_message(message);

	int user_id = db_get_user_id(user_name, db);

	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));
    mx_printerr(date);
	int msg_id_in_chat = db_get_count_msg_for_chat(chat_id, db);

	db_add_msg(msg_id_in_chat + 1, chat_id, user_id, date, text);
	free(text);
	free(message);
}
