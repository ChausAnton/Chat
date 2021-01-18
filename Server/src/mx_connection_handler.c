#include "Chat.h"

void *connection_handler(void *new_sock) {
	int sock_from = *(int *)new_sock;
	int read_size;
	int sock_to;
	char *message;

	char client_message[2000];
	for(int i = 0; i < 2000; i++)
		client_message[i] = '\0';

	char *name = mx_autentification(sock_from);
	if(name == NULL) {
		write(sock_from, "autentification error" , strlen("autentification error"));
		puts("Client disconnected");
		close(sock_from);
		return 0;
	}

	message = mx_strjoin("Hi, ", name);
	message = mx_strjoin(message, ", Who's you want to write ?\n");
	write(sock_from , message , strlen(message));
	free(message);
	if((read_size = recv(sock_from , client_message , 2000 , 0)) > 0) {
		if (strcmp(client_message, "ashp") == 0) {
			for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';
			sock_to = *client_ash;
		}
		else if(strcmp(client_message, "anch") == 0) {
			for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';
			sock_to = *client_anch;
		}
	}

	message = mx_strjoin("Now type something and i shall send it to ", name);
	message = mx_strjoin(message, "\n");
	write(sock_from , message , strlen(message));
	free(message);
	
	while( (read_size = recv(sock_from , client_message , 2000 , 0)) > 0 )
	{
		if(strcmp(client_message, "exit") == 0) {
			puts("Client disconnected");
			write(sock_to , "Client disconnected" , strlen(client_message));
			fflush(stdout);
			break;
		}

		if(strcmp(client_message, "exit") == 0) {
			write(sock_from , "exit" , strlen(client_message));
			break;
		}

		write(sock_to , client_message , strlen(client_message));

		for(int i = 0; i < 2000; i++)
			client_message[i] = '\0';
	}
	
	if(read_size == 0) {
		puts("Client disconnected");
	}
	else if(read_size == -1) {
		perror("recv failed");
	}
		
	close(sock_from);
	return 0;
}
