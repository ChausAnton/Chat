#include "Chat.h"

void read_message(int sock) {
	
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int chat_id = atoi(message);
	/*mx_printerr("char id: ");
	mx_printerr(message);
	mx_printerr("\n");*/

	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	int user_num = atoi(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	int server_num = db_get_count_msg_for_chat(chat_id, db);
	server_access = true;
	send(sock, mx_itoa(server_num), strlen(mx_itoa(server_num)), 0);
	message = clear_client_message(message);
	
	int messages_num = server_num - user_num;

	while(server_access == false) {};
	server_access = false;
	char **messages = get_msg_for_chat_from_the_num(user_num, chat_id, db);//from to 
	server_access = true;
	for(int i = 0; i < messages_num; i++) {
		int size = strlen(messages[i]);

		recv(sock, message, 1000, 0);
		send(sock, mx_itoa(size), strlen(mx_itoa(size)), 0);
		message = clear_client_message(message);

		recv(sock, message, 1000, 0);
		send(sock, messages[i], strlen(messages[i]), 0);
		message = clear_client_message(message);

		mx_printerr("char id: ");
		mx_printerr(mx_itoa(chat_id));
		mx_printerr("\n");

		mx_printerr(messages[i]);
	    mx_printerr("\n");
	}
}


void send_message(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int chat_id = atoi(message);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	char *text = strdup(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	int user_id = db_get_user_id(user_name, db);
	server_access = true;

	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));
    mx_printerr(date);

	while(server_access == false) {};
	server_access = false;
	int msg_id_in_chat = db_get_count_msg_for_chat(chat_id, db);
	server_access = true;

	while(server_access == false) {};
	server_access = false;
	db_add_msg(msg_id_in_chat + 1, chat_id, user_id, date, text);
	server_access = true;

	free(text);
	free(message);
}
