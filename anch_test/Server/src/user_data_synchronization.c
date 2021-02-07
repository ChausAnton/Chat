#include "Chat.h"

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
    }
	//message = clear_client_message(message);
}
