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

		if(strcmp(server_reply, "@image") == 0) {
			printf("image start\n");
			for(int i = 0; i < 2000; i++)
				server_reply[i] = '\0';
			if( recv(sock , server_reply , 2000 , 0) < 0) {
				break;
			}
			int len = atoi(server_reply);
			printf("image size%d\n", len);
			for(int i = 0; i < 2000; i++)
				server_reply[i] = '\0';

			char *binar = (char *)malloc(len + 1);
			for(int i = 0; i < len + 1; i++)
				binar[i] = '\0';
			printf("!!!!!!!!!!!!!!\n");
			if( recv(sock , binar , len , 0) < 0) {
				break;
			}

			printf("%s",binar);
			int ij=0;
        	FILE *write_ptr;
        	write_ptr = fopen("test.jpg","wb");  // w for write, b for binary
			while (ij < len){
        		fwrite(&binar[ij] ,sizeof(binar[ij]),1,write_ptr);
        		ij++;
				if( ! (ij % 16) ) printf( "\n" );
       		}
			fclose(write_ptr);
			continue;
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

		gets(message);
		//fgets(message);
		if(strcmp(message, "@image") == 0) {
			if( send(sock , message , strlen(message) , 0) < 0) {
				puts("Send failed");
				return 1;
			}

			printf("enter image name\n");
			for(int i = 0; i < 1000; i++)
				message[i] = '\0';
			gets(message);
			FILE *file;
        	char *buffer;
        	unsigned long fileLen;

        	//Open file
        	file = fopen(message, "rb");
        	if (!file) {
                fprintf(stderr, "Unable to open file %s", message);
                return 0;
        	}

        	//Get file length
        	fseek(file, 0, SEEK_END);
        	fileLen=ftell(file);
        	fseek(file, 0, SEEK_SET);

        	//Allocate memory
        	buffer=(char *)malloc(fileLen);
        	if (!buffer){
                fprintf(stderr, "Memory error!");
                                fclose(file);
                return 1;
        	}

       		fread(buffer,fileLen,sizeof(char),file);
       		fclose(file);

			if( send(sock , mx_itoa(fileLen) , strlen(mx_itoa(fileLen)) , 0) < 0) {
				puts("Send failed");
				return 1;
			}

			if( send(sock , buffer , strlen(buffer) , 0) < 0){
				puts("Send failed");
				return 1;
			}
			printf("!!!!!!!!!!!!!!\n");
			int i=0;

       		while (i < fileLen){
           		printf("%c ",buffer[i]);
           		i++;
           		if( ! (i % 16) ) printf( "\n" );
       		}
			continue;
		}
		
		if( send(sock , message , strlen(message) , 0) < 0){
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