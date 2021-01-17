#include "Chat.h"

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *serv;
	char message[1000] , server_reply[2000];
	
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
	for(int i = 0; i < 2000; i++)
			server_reply[i] = '\0';

	int i = 0;
	while(1) {

		/*if(i < 1) {
			for(int i = 0; i < 2000; i++)
				server_reply[i] = '\0';
			for(int j = 0; j < 2; j++, i++) {
				if( recv(sock , server_reply , 2000 , 0) < 0) {
					puts("recv failed");
					break;
				}		
				printf("%s", server_reply);
				for(int i = 0; i < 2000; i++)
					server_reply[i] = '\0';
			}
		}*/

		
		if( recv(sock , server_reply , 2000 , 0) < 0) {
			puts("recv failed");
			break;
		}
		
		printf("%s", server_reply);
		
		for(int i = 0; i < 2000; i++)
			server_reply[i] = '\0';

		

		for(int i = 0; i < 1000; i++)
			message[i] = '\0';

		scanf("%s" , message);
		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}

		if(strcmp(message, "exit") == 0) {
			break;
		}
		
		//Receive a reply from the server
		

	}
	
	close(sock);
	return 0;
}