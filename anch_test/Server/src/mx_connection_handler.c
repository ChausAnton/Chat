#include "Chat.h"


void message_send(char *message, int sock_to) {
	time_t t;
    time(&t);

	write(sock_to , message , strlen(message));

	//db_add_msg(int chat_id, int user_id, char* date, char* text)
}

void message_synchronization(char *message, int sock_from) {
	send(sock_from, message, strlen(message), 0);//send @synchronization

	int server_last_id = 0;
	//get last id on server

	//get last id no client
	recv(sock_from, message, 1000, 0);
	int user_last_id = atoi(message);
	if (server_last_id > user_last_id) {
		char **messages;
		//get all message user last id to server last id
		int size = 0;
		int i = 0;

		while (messages[i] != NULL)
			size++;
		send(sock_from, mx_itoa(size), strlen(mx_itoa(size)), 0);
		usleep(20);

		for(int j = 0; messages[j] != NULL; i++) {
			send(sock_from, messages[j], strlen(messages[j]), 0);
			usleep(10);
		}
		send(sock_from, "@end_synchronization", strlen("@end_synchronization"), 0);
	}
	else
		send(sock_from, mx_itoa(-1), strlen(mx_itoa(-1)), 0);
	

}

void search_user(int sock, char *user_name) {
	char *message = clear_client_message(NULL);
	char *user_name2 = clear_client_message(NULL);
	recv(sock, user_name2, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	mx_printerr("IIIIIIIIIIIIII\n");
	message = db_get_user_name(user_name2, db);
	mx_printerr("*************\n");
	send(sock, message, strlen(message), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);
	int user_id = db_get_user_id(user_name2, db);
	send(sock, mx_itoa(user_id), strlen(mx_itoa(user_id)), 0);
	recv(sock, message, 1000, 0);
	mx_printerr("{{{{{{{{{{{{\n");
	message = clear_client_message(message);
}

void new_chat(int sock, char *user_name) {
	char *message = clear_client_message(NULL);

	recv(sock, message, 1000, 0);
	send(sock, "@GET", strlen("@GET"), 0);
	int size = atoi(message);

	db_add_chat(size, "New Chat");
	int last_chat = db_get_last_chat_id();

	message = clear_client_message(message);

	char **users_id = (char **) malloc(sizeof(char *) * size);
	for (int i = 1; i < size; i++) {
		recv(sock, message, 1000, 0);
		send(sock, "@GET", strlen("@GET"), 0);
		users_id[i] = strdup(message);
		db_add_member(last_chat, atoi(message));
		message = clear_client_message(message);
	}

	db_add_member(last_chat, db_get_user_id(user_name, db));

	send(sock, mx_itoa(last_chat), strlen(mx_itoa(last_chat)), 0);
	recv(sock, message, 1000, 0);
	message = clear_client_message(message);
}


void *connection_handler(void *new_sock) {
	int sock_from = *(int *)new_sock;
	int read_size;
	int sock_to;
	char *message;
	char *client_message = clear_client_message(NULL);
	char *user_name = NULL;

	while(1) {
		recv(sock_from , client_message , 2000 , 0);
		send(sock_from, "@GET", strlen("@GET"), 0);

		if(strcmp(client_message, "@sign_up") == 0) {
			user_name = mx_registration(sock_from);
		}
		if (strcmp(client_message, "@sign_in") == 0) {
			user_name = mx_autentification(sock_from);
		}

		client_message = clear_client_message(client_message);

		if (user_name != NULL){ break; }

	}

	mx_printerr("user_data_synchronization start\n");
	user_data_synchronization(sock_from, user_name);
	mx_printerr("user_data_synchronization end\n");

	//while(1) {
		recv(sock_from , client_message , 2000 , 0);
		send(sock_from, "@GET", strlen("@GET"), 0);
		if(strcmp(client_message, "@search") == 0) {
			mx_printerr("user_d@@@@@@@@@@@@@\n");
			search_user(sock_from, user_name);
			mx_printerr("!!!!!!!!!!!!!!\n");

		}
		client_message = clear_client_message(client_message);

		recv(sock_from , client_message , 2000 , 0);
		send(sock_from, "@GET", strlen("@GET"), 0);
		if(strcmp(client_message, "@new_chat") == 0) {
			new_chat(sock_from, user_name);
		}
		client_message = clear_client_message(client_message);

	//}

	mx_printerr("reg fin\n");
	//db_del_user_from_online(user_name, db);
	db_del_user_from_online(user_name, db);
	mx_printerr("Client disconnected");
	free(user_name);
	fflush(stdout);
	close(sock_from);
	return 0;


	if((read_size = recv(sock_from , client_message , 2000 , 0)) > 0) {
		if ((sock_to = db_get_online_user_socket(client_message, db)) != -1) {
			client_message = clear_client_message(client_message);
		}
		else {
			message = strdup("User offline\n");
			write(sock_from , message , strlen(message));
			free(message);
			puts("Client disconnected");
			fflush(stdout);
			close(sock_from);
			db_del_user_from_online(user_name, db);
			free(user_name);
			return 0;
		}
	}

	message = strdup("Now type something");
	write(sock_from , message , strlen(message));
	free(message);
	
	while( (read_size = recv(sock_from , client_message , 2000 , 0)) > 0 )
	{
		if(strcmp(client_message, "exit") == 0) {
			write(sock_from , "exit" , strlen("exit"));
			break;
		}
		else if (strcmp(client_message, "@file") == 0) {
			file_work(sock_from, sock_to);
		}
		else if (strcmp(client_message, "@synchronization") == 0) {
			message_synchronization(client_message, sock_from);
		}
		else {
			message_send(client_message, sock_to);
		}

		client_message = clear_client_message(client_message);
	}
	
	db_del_user_from_online(user_name, db);
	puts("Client disconnected");
	free(user_name);
	
	fflush(stdout);
	close(sock_from);
	return 0;
}
