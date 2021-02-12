#include "Chat.h"

void chat_synchronization(int sock, char *user_name, char *chat_id) {
	if(user_name){}
	char *message = clear_client_message(NULL);

	send(sock, "@size", strlen("@size"), 0);
	recv(sock, message, 1000, 0);
	int size = atoi(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	char **users_id= get_all_user_id_for_chat(atoi(chat_id), db);//get all users
	server_access = true;

	for (int i = 0; i < size; i++) {
		send(sock, users_id[i], strlen(users_id[i]), 0);
		recv(sock, message, 1000, 0);
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
}

void user_data_synchronization(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	while(server_access == false) {};
	server_access = false;
	int user_id = db_get_user_id(user_name, db);
	server_access = true;

	send(sock, mx_itoa(user_id), strlen(mx_itoa(user_id)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//user id

	while(server_access == false) {};
	server_access = false;
	message = db_get_user_name(user_name, db);
	server_access = true;

	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//user name

	while(server_access == false) {};
	server_access = false;
	message = db_get_user_image_path(user_name, db);
	server_access = true;

	if (*message == '\0')
	  message = strdup("resource/images/anonymous.png");//image path
	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//image path

	while(server_access == false) {};
	server_access = false;
	int count_chat_id = get_count_chat_id_for_user(user_id, db);
	server_access = true;	
	send(sock, mx_itoa(count_chat_id), strlen(mx_itoa(count_chat_id)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);// number of chats

	while(server_access == false) {};
	server_access = false;
	char **all_chat_id = get_all_chat_id_for_user(user_id, db);
	server_access = true;

    for(int i = 0; all_chat_id[i] != NULL; i++) {
	    send(sock, all_chat_id[i], strlen(all_chat_id[i]), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//chat id

		while(server_access == false) {};
		server_access = false;
        message = db_get_chat_name(atoi(all_chat_id[i]), db);
		server_access = true;

        send(sock, message, strlen(message), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//chat name

		while(server_access == false) {};
		server_access = false;
        int users_num = get_count_users_for_chat(atoi(all_chat_id[i]), db);
		server_access = true;

        send(sock, mx_itoa(users_num), strlen(mx_itoa(users_num)), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//users number in chat

		chat_synchronization(sock, user_name, all_chat_id[i]);
    }
	//message = clear_client_message(message);
}


