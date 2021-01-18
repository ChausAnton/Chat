#include "Chat.h"

int main(int argc, char *argv[]) {
    int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	
	sqlite3* db;
	db_open("database/uchat.db", &db);
	char *pass = db_get_user_password("áshpigunov", db);
	printf("\náshpigunov password: %s\n", pass);
	pass = db_get_user_password("bubuk", db);
	printf("\nbubuk password: %s\n", pass);
	
	//db_add_user_to_online("áshpigunov", 2141, db);
	//db_add_user_to_online("bubuk", 2142, db);
	//db_del_user_from_online("áshpigunov", db);

	//int sock = db_get_online_user_socket("bubuk", db);
	//printf("\nbubuk socket: %d\n", sock);

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
	server.sin_port = htons( 8555 );
	
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

	char client_message[2000];
	for(int i = 0; i < 2000; i++)
		client_message[i] = '\0';

	int i = 0;
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		write(client_sock, "Do you have account?\n If yes please input 'yes' else input 'no'\n", strlen("Do you have account?\n If yes please input 'yes' else input 'no'\n",))
		if((read_size = recv(sock_from , client_message , 2000 , 0)) > 0){
			if(strcmp(client_message, 'yes')){
				mx_registration(client_sock);
			}
		}
		
		pthread_t sniffer_thread;
		int *new_sock = malloc(1);
		*new_sock = client_sock;
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0) {
			perror("could not create thread");
			return 1;
		}
		
		
		//Now join the thread , so that we dont terminate before the thread
		pthread_join( sniffer_thread , NULL);
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

