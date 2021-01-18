#include "Chat.h"

char *mx_autentification(int sock) {
	char *user_name;
	char *password;
	int read_size;
	char *message;
	char client_message[2000];
	for(int i = 0; i < 2000; i++)
			client_message[i] = '\0';

	message = strdup("Pleas enter your username: ");
	write(sock , message , strlen(message));
	free(message);
	if ((read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
		user_name = strdup(client_message);
		for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';

		message = strdup("Pleas enter your password: ");
		write(sock , message , strlen(message));
		free(message);
		
		if((read_size = recv(sock , client_message , 2000 , 0)) > 0  && 
		(password = db_get_user_password(user_name, db)) != NULL) {
			if(strcmp(password, client_message) == 0) {
				db_add_user_to_online(user_name, sock, db);
				for(int i = 0; i < 2000; i++)
					client_message[i] = '\0';
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
