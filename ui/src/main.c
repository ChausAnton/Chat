#include "../inc/Chat.h"

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


void sock_work(int *sock_new) {
	struct sockaddr_in server;
	struct hostent *serv;
	
	//Create socket
	*sock_new = socket(AF_INET , SOCK_STREAM , 0);

	//puts("Socket created");

	serv = gethostbyname(ip);
    memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	memcpy(&server.sin_addr.s_addr, serv->h_addr_list[0],  serv->h_length);
	server.sin_port = htons(serverport);
	//Connect to remote server
	if (connect(*sock_new , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//perror("connect failed. Error");
		return;
	}	
	//puts("Connected\n");
	return;
}



int main(int argc, char *argv[]) {
	if(argc <= 2) {
		mx_printerr("usage: ./ucaht [SERVERADDR] [SERVERPORT]\n");
		exit(0);
	}
	ip = strdup(argv[1]);
	serverport = atoi(argv[2]);

    sock_work(&sock);

	new_user = false;
	thread_info = NULL;
	exit_thread = false;
	sniffer_thread = NULL;
	barashka = true;
	if( pthread_create( &sniffer_thread , NULL ,  reader , NULL) < 0) {
		//perror("could not create thread");
		return 1;
	}

	////mx_printerr("socket to: ");
   // //mx_printerr(mx_itoa(sock));
    ////mx_printerr("\n");

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
	
	main_data.main_box.css = "ui/resource/styles/main_screen.css";
    main_data.login_box.css = "ui/resource/styles/sign_in.css";
    main_data.reg_box.css = "ui/resource/styles/sign_up.css";
    main_data.reload_box.css = "ui/resource/styles/reload_screen.css";

    start_screen();
     
    gtk_widget_show_all(main_data.window);
    g_signal_connect(main_data.window, "destroy", G_CALLBACK(exit_client), NULL);
    gtk_main();

    //pthread_join(sniffer_thread , NULL);
    close(sock);
    return 0;
}
