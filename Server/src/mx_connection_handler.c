#include "Chat.h"

void *connection_handler(void *new_sock) {
	int sock_from = *(int *)new_sock;
	int read_size;
	int sock_to;
	char *message;
	char *client_message = clear_client_message(NULL);

	mx_registration(sock_from);
	
	char *user_name = NULL;
	while(user_name == NULL) {
		user_name = mx_autentification(sock_from);
	}

	message = mx_strjoin("Hi, ", user_name);
	message = mx_strjoin(message, ", Who's you want to write ?\n");
	write(sock_from , message , strlen(message));
	free(message);

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

		write(sock_to , client_message , strlen(client_message));

		client_message = clear_client_message(client_message);
	}
	
	db_del_user_from_online(user_name, db);
	puts("Client disconnected");
	free(user_name);
	
	fflush(stdout);
	close(sock_from);
	return 0;
}
