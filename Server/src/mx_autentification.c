#include "Chat.h"

char *mx_autentification(int sock) {
	char *user_name;
	char *password;
	int read_size;
	char *message;
	char *client_message = clear_client_message(NULL);


	message = strdup("Pleas enter your username: ");
	write(sock , message , strlen(message));
	free(message);
	if ((read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
		user_name = strdup(client_message);
		client_message = clear_client_message(client_message);

		message = strdup("Pleas enter your password: ");
		write(sock , message , strlen(message));
		free(message);
		
		if((read_size = recv(sock , client_message , 2000 , 0)) > 0  && 
		(password = db_get_user_password(user_name, db)) != NULL) {
			if(strcmp(password, client_message) == 0) {
				db_add_user_to_online(user_name, sock, db);
				client_message = clear_client_message(client_message);
				return user_name;
			}
		}

		message = strdup("Oops, something wrong with your login or password\nTry again!!!!");
		write(sock , message , strlen(message));
		free(message);
		fflush(stdout);
		
	}
	return NULL;
}
