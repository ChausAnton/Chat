#include "Chat.h"

void read_file(int sock) {
	char file_n[20];
	for(int i = 0; i < 20; i++)
		file_n[i] = '\0';

	recv(sock , file_n , 20 , 0);
	char *extension = mx_strsplit(file_n, '.')[1];
	char *file_name = mx_strjoin("c1.", extension);
	char p_array[1000];
	
	printf("Reading file Size\n");
	FILE *file = fopen(file_name, "wb");

	recv(sock , p_array , 1000 , 0);//size
	int b64_size = atoi(p_array);
    /*unsigned char *b64 = (unsigned char *) malloc(sizeof(unsigned char) * b64_size);

	for(int i = 0; i < b64_size; i++)
		b64[i] = '\0';
		
	recv(sock , b64 , b64_size , 0);*/

    unsigned char *b64 = NULL;
    int nb = 0;
	char buf[50001];
	for(int i = 0; i < 50001; i++) {
		buf[i] = '\0';
	}

	while(nb < b64_size) {
		nb += recv(sock , buf , 50000 , 0);
		b64 = (unsigned char *)mx_strjoin((char *)b64, buf);
	}

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


void file_sending(int sock) {
	write(sock , "@file" , strlen("@file"));
	char message[1000];
	printf("input file name:\n");
	gets(message);
	send(sock , message, strlen(message), 0);
	usleep(50000);
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
	send(sock , send_buffer, b64_len, 0);
    send(sock , "", 0, 0);
	printf("size %zu\n", b64_len);
	usleep(50000);

	printf("file send end\n");
	fclose(picture);
}
