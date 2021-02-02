#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>

///server
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>

#define SERVERPORT 8444
#define SERVERADDR "localhost"

void mx_swap_char(char *s1, char *s2) {
    char temp = *s1;
    char temp2 = *s2;
    
    *s2 = temp;
    *s1 = temp2;
}

char *mx_strnew(const int size) {

    char *str = (char*) malloc((size + 1) * sizeof(char));

    if (str == NULL || size < 0) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
    str[size] = '\0';
    return str;
}

int mx_strlen(const char *s) {
    int j = 0;
    char i = s[0];
    while(i != '\0') {
        j++;
        i = s[j];
    }
    return j;
}

void mx_str_reverse(char *s) {
    int len = strlen(s);
    
    for (int i = 0; i < len/2; i++) {
        mx_swap_char(&s[i], &s[len - 1 - i]);
    }
}


char *mx_itoa(int number) {
    int lenght = 0;
    unsigned int num = number;
    while (num != 0)
    {
        num = num / 10;
        lenght++;
    }
    
    char *arr = NULL;
    arr = strnew(lenght);
    bool min = false;
    num = number;
    int i = 0;
    if (number == 0) return strcpy(arr, "0");

    if (number < 0) {
        min = true;
        num = num * -1;
    } 
    
    while(num != 0) {
        arr[i] = (num % 10) + 48;
        num = num / 10;
        i++;
    }
    if(min == true) arr[i] = '-';
    mx_str_reverse(arr);
    return arr;
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
	if( pthread_create( &sniffer_thread , NULL ,  read , (void*) new_sock) < 0) {
		perror("could not create thread");
		return 1;
	}

		//Get Picture Size
                printf("Getting Picture Size\n");
                FILE *picture;
                picture = fopen(argv[1], "r");
                int size;

                char send_buffer[1]; // no link between BUFSIZE and the file size
                int nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
                while(!feof(picture)) {
                        write(sock, send_buffer, nb);
                        nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
                        // no need to bzero
                }
                printf("!!!!!!!!!!!!!!!!!!\n");
                /*fseek(picture, 0, SEEK_END);
                size=ftell(picture);
                fseek(picture, 0, SEEK_SET);

                printf("%d\n", size);

                //Send Picture Size
                printf("Sending Picture Size\n");
                write(sock, mx_itoa(size) , strlen(mx_itoa(size)));

                //Send Picture as Byte Array
                printf("Sending Picture as Byte Array\n");
                char send_buffer[size];
                while(!feof(picture)) {
                fread(send_buffer, sizeof(send_buffer), 1, picture);
                write(sock, send_buffer, sizeof(send_buffer));
                bzero(send_buffer, sizeof(send_buffer));
                }*/
                


	pthread_join(sniffer_thread , NULL);
	close(sock);
	return 0;
}

//int main (int argc , char * argv [] ){





        // argv[1] = 1.jpg

       /* FILE *file;
        char *buffer;
        unsigned long fileLen;

        //Open file
        file = fopen(argv[1], "rb");
        if (!file)
        {
                fprintf(stderr, "Unable to open file %s", argv[1]);
                return 0;
        }

        //Get file length
        fseek(file, 0, SEEK_END);
        fileLen=ftell(file);
        fseek(file, 0, SEEK_SET);

        //Allocate memory
        buffer=(char *)malloc(fileLen);
        if (!buffer)
        {
                fprintf(stderr, "Memory error!");
                                fclose(file);
                return 1;
        }

       fread(buffer,fileLen,sizeof(char),file);
       fclose(file);

       int i=0;

        FILE *write_ptr;
        write_ptr = fopen("test.jpg","wb");  // w for write, b for binary
        char temp[fileLen];
       while (i < fileLen){
           //fwrite(&buffer[i] ,sizeof(buffer[i]),1,write_ptr);
           sprintf(&temp[i],"%02X",buffer[i]);
           i++;
           if( ! (i % 16) ) printf( "\n" );
       }

        while (i < fileLen){
           fwrite(&temp[i] ,sizeof(temp[i]),1,write_ptr);
           i++;
           if( ! (i % 16) ) printf( "\n" );
       }
        
    
    fclose(write_ptr);

        return 0;*/

//}
