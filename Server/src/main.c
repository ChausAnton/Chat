#include "Chat.h"

void sock_close() {
	close(global_sock);
	exit(0);
}

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
}

int main(int argc, char *argv[]) {

	if(argc <= 1) {
		mx_printerr("usage: ./server [SERVERPORT]\n");
		exit(0);
	}
	serverport = atoi(argv[1]);

	skeleton_daemon();
	printf("Sever PID: %d\n", getpid());

    int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	server_access = true;
	db_open("database/uchat.db", &db);

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
	}
	global_sock = socket_desc;
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(serverport);
	
	signal(SIGINT, sock_close);
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
		return 1;
	}
	
	//Listen
	listen(socket_desc , 0x100);	
	
	//Accept an incoming connection
	c = sizeof(struct sockaddr_in);

	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {

		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0) {
			return 1;
		}

		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL);
	}
	close(socket_desc);
	if (client_sock < 0) {
		return 1;
	}
	
	return 0;
}

