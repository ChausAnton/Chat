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

		if (strcmp(client_message, "@image") == 0) {
			write(sock_to , "@image" , strlen("@image"));
			char image_name[20];
			(read_size = recv(sock_from , image_name , 20 , 0));
			write(sock_to , image_name , strlen(image_name));
			printf("Reading Picture\n");
            char p_array[1000];

			printf("Reading Picture Size\n");

			recv(sock_from , p_array , 1000 , 0);
			send(sock_to , p_array, strlen(p_array), 0);//size
			int b64_size = atoi(p_array);
						
			unsigned char b64[b64_size];
			for(int i = 0; i < b64_size; i++)
				b64[i] = '\0';
			recv(sock_from , b64 , b64_size , 0);
			send(sock_to , b64, b64_size, 0);
			printf("Reading Picture End\n");
			
			continue;
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
