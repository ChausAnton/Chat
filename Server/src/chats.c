#include "Chat.h"

void delete_chat(int sock) {
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int char_id = atoi(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	db_del_chat(char_id, db);
	server_access = true;
}

void new_chat_from_server(int sock) {

	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GETst", strlen("@GETst"), 0);
	int user_id = atoi(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	char **all_chat_id = get_all_chat_id_for_user(user_id, db);
	server_access = true;
	int size = 0;
	while(all_chat_id[size] != NULL)
		size++;

	recv(sock, message, 1000, 0);
	int user_chats_num = atoi(message);
	send(sock, "@GETnd", strlen("@GETnd"), 0);
	message = clear_client_message(message);

	recv(sock, message, 1000, 0);
	send(sock, mx_itoa(size), strlen(mx_itoa(size)), 0);
	//mx_printerr("ITOA SIZE: ");
	//mx_printerr(mx_itoa(size));
	//mx_printerr("\n");
	message = clear_client_message(message);

	int new_chats_num = size - user_chats_num;
	if(new_chats_num > 0) {
		for(int i = 0; i < user_chats_num; i++) {
			all_chat_id++;
		}
	}
	for(int i = 0; i < new_chats_num; i++) {
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

		recv(sock, message, 1000, 0);
		while(server_access == false) {};
		server_access = false;
		int num_users_for_chat = get_count_users_for_chat(atoi(all_chat_id[i]), db);
		server_access = true;
		send(sock, mx_itoa(num_users_for_chat), strlen(mx_itoa(num_users_for_chat)), 0);
		message = clear_client_message(message);

		while(server_access == false) {};
		server_access = false;
		char **users_id = get_all_user_id_for_chat(atoi(all_chat_id[i]), db);
		server_access = true;

		for(int j = 0; j < num_users_for_chat; j++) {
			recv(sock, message, 1000, 0);
			send(sock, users_id[j], strlen(users_id[j]), 0);
			message = clear_client_message(message);

			recv(sock, message, 1000, 0);
			while(server_access == false) {};
			server_access = false;
			char *login = db_get_user_login(atoi(users_id[j]), db);
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
			free(user_name);

			recv(sock, message, 1000, 0);
			while(server_access == false) {};
			server_access = false;
			char *image_path = db_get_user_image_path(login, db);
			server_access = true;
			if (*image_path == '\0')
				image_path = strdup("ui/resource/images/anonymous.png");

			send(sock, image_path, strlen(image_path), 0);
			message = clear_client_message(message);
			free(login);
			free(image_path);
		}
	}

	if(new_chats_num < 0) {
		for(int i = 0; i < size; i++) {
			recv(sock, message, 1000, 0);
			send(sock, all_chat_id[i], strlen(all_chat_id[i]), 0);
			message = clear_client_message(message);
		}
	}
}

void read_message(int sock) {
	
	char *message = clear_client_message(NULL);
	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int chat_id = atoi(message);
	/*//mx_printerr("char id: ");
	//mx_printerr(message);
	//mx_printerr("\n");*/

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

		//mx_printerr("char id: ");
		//mx_printerr(mx_itoa(chat_id));
		//mx_printerr("\n");

		//mx_printerr(messages[i]);
	    //mx_printerr("\n");
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
    //mx_printerr(date);

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
