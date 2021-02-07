#include "Chat.h"

void file_work(int sock_from, int sock_to) {
	write(sock_to , "@file" , strlen("@file"));
	char *file_n = NULL;
    file_n = clear_client_message(file_n);

	recv(sock_from , file_n , 20 , 0);
	write(sock_to , file_n , strlen(file_n));
	

    char *extension = mx_strsplit(file_n, '.')[1];
	char *file_name = mx_strjoin("c1.", extension);
	FILE *file = fopen(file_name, "wb");

    char p_array[1000];	

	printf("Reading file Size\n");

	recv(sock_from , p_array , 1000 , 0);
	send(sock_to , p_array, strlen(p_array), 0);//size
	int b64_size = atoi(p_array);

	unsigned char *b64 = NULL;


	int nb = 0;
	char buf[50001];
	for(int i = 0; i < 50001; i++) {
		buf[i] = '\0';
	}

	while(nb < b64_size) {
		nb += recv(sock_from , buf , 50000 , 0);
		b64 = (unsigned char *)mx_strjoin((char *)b64, buf);
		for(int i = 0; i < 50001; i++) {
		    buf[i] = '\0';
	    }
	}

	unsigned char *b64_fin;
	if(strlen((char *)b64) < b64_size) {
		b64_fin = (unsigned char *)mx_strjoin(mx_strsplit(p_array, '@')[1], (char *)b64);
	}
	else
		b64_fin = (unsigned char *)b64;

	send(sock_to , b64, b64_size, 0);


	size_t b64_dec_len = b64_size * 3 / 4;
	unsigned char *b64_dec = base64_decode(b64_fin, b64_size, &b64_dec_len);
	fwrite(b64_dec, b64_dec_len, 1, file);
	fclose(file);
	
	free(file_name);
	free(extension);
	free(b64);
	free(b64_dec);

	printf("Reading file End\n");
}

	