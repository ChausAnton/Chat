#include "Chat.h"

void *reader(void *new_sock) {
	int sock = *(int *)new_sock;
	char server_reply[2000];
	for(int i = 0; i < 2000; i++)
			server_reply[i] = '\0';

	while(1) {
		if( recv(sock , server_reply , 2000 , 0) < 0) {
			break;
		}
		if(strcmp(server_reply, "exit") == 0) {
			close(sock);
			break;
		}
		
		printf("%s\n", server_reply);
		
		for(int i = 0; i < 2000; i++) {
			server_reply[i] = '\0';
		}
	}
	return 0;
}


int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *serv;
	char message[1000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	serv = gethostbyname(SERVERADDR);
    memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	memcpy(&server.sin_addr.s_addr, serv->h_addr_list[0],  serv->h_length);
	server.sin_port = htons(SERVERPORT);
	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}	
	puts("Connected\n");
	
	//keep communicating with server
	
	pthread_t sniffer_thread;
	int *new_sock = malloc(1);
	*new_sock = sock;
	if( pthread_create( &sniffer_thread , NULL ,  reader , (void*) new_sock) < 0) {
		perror("could not create thread");
		return 1;
	}

	while(sniffer_thread) {
		
		for(int i = 0; i < 1000; i++)
			message[i] = '\0';

		scanf("%s" , message);
		
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}

		if(strcmp(message, "exit") == 0) {
			break;
		}
		
	}
	pthread_join(sniffer_thread , NULL);
	close(sock);
	return 0;
}