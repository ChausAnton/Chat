#include "Chat.h"

char *mx_autentification(int sock) {
	int read_size;
	char *message;
	char client_message[2000];
	for(int i = 0; i < 2000; i++)
			client_message[i] = '\0';

	message = strdup("Pleas enter your username: ");
	write(sock , message , strlen(message));
	free(message);
	if ((read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
		message = strdup("Pleas enter your password: ");
		write(sock , message , strlen(message));
		free(message);
		if(strcmp(client_message, "ashp") == 0) {
			for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';
			if ((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
				if(strcmp(client_message, "0000") == 0) {
					client_ash = &sock;
					return strdup("ashp");
				}
			}
		}
		else if(strcmp(client_message, "anch") == 0) {
			for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';
			if ((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
				if(strcmp(client_message, "1111") == 0) {
					client_anch = &sock;
					return strdup("anch");
				}
			}
		}
		
	}
	return NULL;
}
