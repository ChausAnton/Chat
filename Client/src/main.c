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

		if (strcmp(server_reply, "@image") == 0) {
			char image_name[20];
			recv(sock , image_name , 20 , 0);

			recv(sock ,  server_reply, 2000 , 0);
			int size = atoi(server_reply);

			printf("Reading Picture\n");
            char p_array[1];
            FILE *image = fopen("c1.jpg", "w");
            int nb = read(sock, p_array, 1);
            while (size >= 1) {
                fwrite(p_array, 1, nb, image);
                nb = read(sock, p_array, 1);
				size--;
            }
            fclose(image);
			send(sock , "@@end" , strlen("@@end") , 0);
			for(int i = 0; i < 2000; i++) {
				server_reply[i] = '\0';
			}
			printf("@@@@@@@@@@@@@\n");
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

		if (strcmp(message, "@image") == 0) {
			write(sock , "@image" , strlen("@image"));

			printf("input image name:\n");
			gets(message);
			write(sock , message , strlen(message));

            FILE *picture;
			picture = fopen(message, "r");
			fseek(picture, 0, SEEK_END);
			int size = ftell(picture);
			fseek(picture, 0, SEEK_SET);

			write(sock , mx_itoa(size) , strlen(mx_itoa(size)));

            
            char send_buffer[1]; // no link between BUFSIZE and the file size
            int nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
            while(!feof(picture)) {
                write(sock, send_buffer, nb);
                nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
            }
			write(sock, " ", 1);
			printf("!!!!!!\n");
			fclose(picture);
			recv(sock, message, 3 , 0);
			printf("&&&&&&&&&&&&&\n");
			continue;
		}
		
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