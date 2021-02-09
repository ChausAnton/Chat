#include "Chat.h"

void chat_synchronization(int sock, char *user_name, char *chat_id) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int size = atoi(message);
	message = clear_client_message(message);

	char **users_id= get_all_user_id_for_chat(atoi(chat_id), db);//get all users

	for (int i = 0; i < size; i++) {
		send(sock, users_id[i], strlen(users_id[i]), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);

		char *login = db_get_user_login(atoi(users_id[i]), db);
		send(sock, login, strlen(login), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//user login

		message = db_get_user_name(login, db);
		send(sock, message, strlen(message), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//user name

		message = db_get_user_image_path(login, db);
		if (*message == '\0')
			message = strdup("resource/images/anonymous.png");

		send(sock, message, strlen(message), 0);
		recv(sock, message, 1000, 0);
		message = clear_client_message(message);//image path
	}
}

void user_data_synchronization(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	int user_id = db_get_user_id(user_name, db);
	send(sock, mx_itoa(user_id), strlen(mx_itoa(user_id)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//user id

	message = db_get_user_name(user_name, db);
	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//user name

	message = db_get_user_image_path(user_name, db);
	if (*message == '\0')
		message = strdup("resource/images/anonymous.png");//image path
	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);//image path

	int count_chat_id = get_count_chat_id_for_user(user_id, db);	
	send(sock, mx_itoa(count_chat_id), strlen(mx_itoa(count_chat_id)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);// number of chats

	

	char **all_chat_id = get_all_chat_id_for_user(user_id, db);
    for(int i = 0; all_chat_id[i] != NULL; i++) {
	    send(sock, all_chat_id[i], strlen(all_chat_id[i]), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//chat id

        message = db_get_chat_name(atoi(all_chat_id[i]), db);
        send(sock, message, strlen(message), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//chat name

        int users_num = get_count_users_for_chat(atoi(all_chat_id[i]), db);
        send(sock, mx_itoa(users_num), strlen(mx_itoa(users_num)), 0);
	    recv(sock, message, 1000, 0);
        message = clear_client_message(message);//users number in chat

		chat_synchronization(sock, user_name, all_chat_id[i]);
    }
	//message = clear_client_message(message);
}


