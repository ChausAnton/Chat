#include "Chat.h"

int chat_id_g;

void *connection_handler(void *new_sock) {
	int sock_from = *(int *)new_sock;
	/*int read_size;
	int sock_to;
	char *message;*/
	char *client_message = clear_client_message(NULL);
	char *user_name = NULL;
	int exit_code = 1;

	//mx_printerr(mx_itoa(sock_from));
	//mx_printerr("\n");
	while(1) {
		recv(sock_from , client_message , 2000 , 0);
		send(sock_from, "@GET", strlen("@GET"), 0);
		//mx_printerr(client_message);
		//mx_printerr("\n\n");

		if(strcmp(client_message, "@sign_up") == 0) {
			user_name = mx_registration(sock_from);
		}
		if (strcmp(client_message, "@sign_in") == 0) {
			user_name = mx_autentification(sock_from);
		}

		if(strcmp(client_message, "@synchronization") == 0) {
			mx_printerr("user_data_synchronization start\n");
			user_data_synchronization(sock_from, user_name);
			mx_printerr("user_data_synchronization end\n");
		}

		if(strcmp(client_message, "@search") == 0) {
			search_user(sock_from);

		}

		if(strcmp(client_message, "@new_chat") == 0) {
			new_chat(sock_from, user_name);
		}
		if (strcmp(client_message, "@message_send") == 0) {
			send_message(sock_from, user_name);
		}
		if(strcmp(client_message, "@add_new_user") == 0) {
			add_user_to_chat(sock_from);
		}
		if (strcmp(client_message, "@message_read") == 0) {
			read_message(sock_from);
		}
		if (strcmp(client_message, "@new_chat_from_server") == 0) {
			new_chat_from_server(sock_from);
		}
		if(strcmp(client_message, "@save_edit_chat_changes") == 0) {
			save_edit_chat_changes(sock_from);
		}
		if(strcmp(client_message, "@send_edit_chat_changes") == 0) {
			send_edit_chat_changes(sock_from);
		}
		if (strcmp(client_message, "@exit_client") == 0) {
			db_del_user_from_online(user_name, db);
			free(user_name);
			fflush(stdout);
			close(sock_from);
			mx_printerr("Client out\n");
			pthread_exit(&exit_code);
			return 0;
		}
		if (strcmp(client_message, "@exit_thread") == 0) {
			fflush(stdout);
			close(sock_from);
			mx_printerr("Client thread out\n");
			pthread_exit(&exit_code);
			return 0;
		}
		if(strcmp(client_message, "@exit_from_online") == 0) {
			db_del_user_from_online(user_name, db);
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
