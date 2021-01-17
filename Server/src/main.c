#include "Chat.h"

int *client_anch, *client_ash;


void *connection_handler(void *name_user);

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



int main(int argc, char *argv[]) {
    int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8433 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 0x100);	
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	int i = 0;
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		
		pthread_t sniffer_thread;
		int *new_sock = malloc(1);
		*new_sock = client_sock;
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0) {
			perror("could not create thread");
			return 1;
		}
		
		
		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL);
		puts("Handler assigned");
		
	}
	close(socket_desc);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *new_sock)
{
	//Get the socket descriptor
	int sock_from = *(int *)new_sock;
	int read_size;
	int sock_to;
	char *message;

	char client_message[2000];
	for(int i = 0; i < 2000; i++)
				client_message[i] = '\0';

	char *name = mx_autentification(sock_from);
	printf("%s\n", name);
	if(name == NULL) {
		write(sock_from, "autentification error" , strlen("autentification error"));
		puts("Client disconnected");
		return 0;
	}

	/*if(strcmp(name, "anch")) {
		sock_from = *client_anch;
	}
	if(strcmp(name, "ashp")) {
		sock_from = *client_ash;
	}*/

	
	//Send some messages to the client
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
	
	//Receive a message from client
	while( (read_size = recv(sock_from , client_message , 2000 , 0)) > 0 )
	{
		if(strcmp(client_message, "exit") == 0) {
			puts("Client disconnected");
			write(sock_to , "Client disconnected" , strlen(client_message));
			fflush(stdout);
			break;
		}
		//Send the message back to client
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
		
	//Free the socket pointer
	
	return 0;
}
