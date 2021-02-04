#include "Chat.h"

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void read_file(int sock) {
	char file_n[20];
	for(int i = 0; i < 20; i++)
		file_n[i] = '\0';

	recv(sock , file_n , 20 , 0);
	char *extension = mx_strsplit(file_n, '.')[1];
	printf("extension %s\n", extension);
	char *file_name = mx_strjoin("c1.", extension);
	printf("file_name %s\n", file_name);
	char p_array[1000];
	
	printf("Reading file Size\n");
	FILE *file = fopen(file_name, "wb");

	recv(sock , p_array , 1000 , 0);//size
	int b64_size = atoi(p_array);
	unsigned char b64[b64_size];

	for(int i = 0; i < b64_size; i++)
		b64[i] = '\0';
		
	recv(sock , b64 , b64_size , 0);

	printf("size: %s\n", p_array);

	unsigned char *b64_fin;
	if(strlen((char *)b64) < b64_size) {
		b64_fin = (unsigned char *)mx_strjoin(mx_strsplit(p_array, '@')[1], (char *)b64);
	}
	else
		b64_fin = (unsigned char *)b64;

	size_t b64_dec_len = b64_size * 3 / 4;
	unsigned char *b64_dec = base64_decode(b64_fin, b64_size, &b64_dec_len);
	fwrite(b64_dec, b64_dec_len, 1, file);
	fclose(file);
	printf("Reading file End\n");
}


void *reader(void *new_sock) {
	int sock = *(int *)new_sock;
	char *server_reply = NULL;
	server_reply = clear_client_message(server_reply);
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

		if (strcmp(server_reply, "@file") == 0) {
			read_file(sock);
			server_reply = clear_client_message(server_reply);
			continue;
		}
		
		printf("%s\n", server_reply);
		
		server_reply = clear_client_message(server_reply);
	}
	return 0;
}


void file_sending(int sock) {
	write(sock , "@file" , strlen("@file"));
	char message[1000];
	printf("input file name:\n");
	gets(message);
	send(sock , message, strlen(message), 0);
	usleep(50000);
	printf("name %s\n", message);
    FILE *picture;
	picture = fopen(message, "rb");
	fseek(picture, 0, SEEK_END);
	int size = ftell(picture);
	fseek(picture, 0, SEEK_SET);
	unsigned char buffer[size];
	fread(buffer, size, 1, picture);

	size_t b64_len = 0;
	unsigned char  *send_buffer = base64_encode(buffer, size, &b64_len);

	//char *send_size = mx_strjoin(mx_itoa(b64_len), "@");
	char *send_size = mx_itoa(b64_len);
	send(sock , send_size, strlen(send_size), 0);
	usleep(50000);	
	printf("size %s\n", send_size);
	char check[100];
	send(sock , send_buffer, b64_len, 0);
	usleep(50000);

	printf("file send end\n");
	fclose(picture);
}


int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *serv;
	char *message = NULL;
	
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
		
		message = clear_client_message(message);

		gets(message);

		if (strcmp(message, "@file") == 0) {
			file_sending(sock);
			message = clear_client_message(message);
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