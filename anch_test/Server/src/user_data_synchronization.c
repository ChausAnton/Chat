#include "Chat.h"

void chat_synchronization(int sock, char *user_name, char *chat_id) {
	if(user_name){};
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@size", strlen("@size"), 0);
	int size = atoi(message);
	message = clear_client_message(message);

	while(server_access == false) {};
	server_access = false;
	char **users_id= get_all_user_id_for_chat(atoi(chat_id), db);//get all users
	server_access = true;

	for (int i = 0; i < size; i++) {
		recv(sock, message, 1000, 0);
		send(sock, users_id[i], strlen(users_id[i]), 0);
		message = clear_client_message(message);

		while(server_access == false) {};
		server_access = false;
		char *login = db_get_user_login(atoi(users_id[i]), db);
		server_access = true;

		recv(sock, message, 1000, 0);
		send(sock, login, strlen(login), 0);
		message = clear_client_message(message);//user login

		while(server_access == false) {};
		server_access = false;
		char *name = db_get_user_name(login, db);
		server_access = true;

		recv(sock, message, 1000, 0);
		send(sock, name, strlen(name), 0);
		free(name);
		message = clear_client_message(message);//user name

		while(server_access == false) {};
		server_access = false;
		char *image_path = db_get_user_image_path(login, db);
		server_access = true;
		if (*image_path == '\0')
			image_path = strdup("resource/images/anonymous.png");

		recv(sock, message, 1000, 0);
		send(sock, image_path, strlen(image_path), 0);
		free(image_path);
		message = clear_client_message(message);//image path
	}
}

void user_data_synchronization(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	while(server_access == false) {};
	server_access = false;
	int user_id = db_get_user_id(user_name, db);
	server_access = true;

	recv(sock, message, 1000, 0);
	send(sock, mx_itoa(user_id), strlen(mx_itoa(user_id)), 0);
	message = clear_client_message(message);//user id

	while(server_access == false) {};
	server_access = false;
	char *name= db_get_user_name(user_name, db);
	server_access = true;

	recv(sock, message, 1000, 0);
	send(sock, name, strlen(name), 0);
	free(name);
	message = clear_client_message(message);//user name

	while(server_access == false) {};
	server_access = false;
	char *image_path = db_get_user_image_path(user_name, db);
	server_access = true;

	if (*image_path == '\0')
	  image_path = strdup("resource/images/anonymous.png");//image path
	recv(sock, message, 1000, 0);
	send(sock, image_path, strlen(image_path), 0);
	free(image_path);
	message = clear_client_message(message);//image path

	while(server_access == false) {};
	server_access = false;
	int count_chat_id = get_count_chat_id_for_user(user_id, db);
	server_access = true;	
	recv(sock, message, 1000, 0);
	send(sock, mx_itoa(count_chat_id), strlen(mx_itoa(count_chat_id)), 0);
	message = clear_client_message(message);// number of chats

	while(server_access == false) {};
	server_access = false;
	char **all_chat_id = get_all_chat_id_for_user(user_id, db);
	server_access = true;

    for(int i = 0; all_chat_id[i] != NULL; i++) {
	    recv(sock, message, 1000, 0);
	    send(sock, all_chat_id[i], strlen(all_chat_id[i]), 0);
        message = clear_client_message(message);//chat id

		while(server_access == false) {};
		server_access = false;
        char *chat_name = db_get_chat_name(atoi(all_chat_id[i]), db);
		server_access = true;

	    recv(sock, message, 1000, 0);
        send(sock, chat_name, strlen(chat_name), 0);
		free(chat_name);
        message = clear_client_message(message);//chat name

		while(server_access == false) {};
		server_access = false;
        int users_num = get_count_users_for_chat(atoi(all_chat_id[i]), db);
		server_access = true;

	    recv(sock, message, 1000, 0);
        send(sock, mx_itoa(users_num), strlen(mx_itoa(users_num)), 0);
        message = clear_client_message(message);//users number in chat

		chat_synchronization(sock, user_name, all_chat_id[i]);
    }
	//message = clear_client_message(message);
}


