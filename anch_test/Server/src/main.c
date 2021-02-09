#include "Chat.h"


int main(int argc, char *argv[]) {
    int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	
	db_open("database/uchat.db", &db);

	db_add_user("a", "1");
	db_add_user("s", "1");
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(SERVERPORT);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 0x100);	
	
	//Accept an incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	int i = 0;
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
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

	perror("!!!!!!!!!!!!!!!sdfd\n");
	close(socket_desc);
	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

