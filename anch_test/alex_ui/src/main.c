#include "Chat.h"

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void message_synchronization(char *message, int sock) {

	int last_message_id = 0;
	//func to get last message id
	send(sock, mx_itoa(last_message_id), strlen(mx_itoa(last_message_id)), 0);
	
	//number of message
	recv(sock, message, 2000, 0);
	int number_message = atoi(message);

	if (number_message > 0) {
		char **messages = (char **) malloc(sizeof(char *) * (number_message + 1));
		int i = 0;
		recv(sock, message, 2000, 0);
		while(strcmp("@end_synchronization", message) != 0) {
			messages[i] = strdup(message);
			i++;
			recv(sock, message, 2000, 0);
		}
		messages[i] = NULL;
		//func to add new messages to DB
		for(int i = 0; i < number_message; i++) {
			free(messages[i]);
		}
		free(messages);
	}
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
		else if(strcmp(server_reply, "@synchronization") == 0) {
			message_synchronization(server_reply, sock);
		}
		else if (strcmp(server_reply, "@file") == 0) {
			//read_file(sock);
			server_reply = clear_client_message(server_reply);
			continue;
		}
		
		printf("%s\n", server_reply);
		
		server_reply = clear_client_message(server_reply);
	}
	return 0;
}


void sock_work() {
	struct sockaddr_in server;
	struct hostent *serv;
	
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
		return;
	}	
	puts("Connected\n");
	
	//keep communicating with server
	
	int *new_sock = malloc(1);
	*new_sock = sock;
	/*if( pthread_create( &sniffer_thread , NULL ,  reader , (void*) new_sock) < 0) {
		perror("could not create thread");
		return;
	}*/

	//while(sniffer_thread) {}

	//pthread_join(sniffer_thread , NULL);
	//close(sock);
	return;
}


int main(int argc, char *argv[]) {
    sock_work();
    gtk_init(&argc, &argv);

    main_data.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_data.window), "Nichat");
    gtk_window_set_resizable(GTK_WINDOW(main_data.window), FALSE);
    gtk_window_set_position(GTK_WINDOW(main_data.window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(main_data.window), WINDOW_SIZE_X, WINDOW_SIZE_Y);

    main_data.activity = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(main_data.activity), "activity");
    gtk_container_add(GTK_CONTAINER(main_data.window), main_data.activity);
    
    main_data.activity_block = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_data.activity_block), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_container_add(GTK_CONTAINER(main_data.activity), main_data.activity_block);
    //g_signal_connect(window, "activate-default", G_CALLBACK(start_screen), (void *)activity_block);
    main_data.styles = gtk_css_provider_new();
    //gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_data.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    start_screen();
     
    gtk_widget_show_all(main_data.window);
    g_signal_connect(main_data.window, "destroy", G_CALLBACK(exit_client), NULL);
    gtk_main();

    //pthread_join(sniffer_thread , NULL);
    close(sock);
    return 0;
}
