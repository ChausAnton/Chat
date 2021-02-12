#include "Chat.h"

char *mx_autentification(int sock) {
	char *user_name;
	char *password = NULL;
	int read_size;
	//char *message;
	char *client_message = clear_client_message(NULL);

	if ((read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
		send(sock, "@GET", strlen("@GET"), 0);
		
		user_name = strdup(client_message);
		client_message = clear_client_message(client_message);
		
		if((read_size = recv(sock , client_message , 2000 , 0)) > 0  && 
		(password = db_get_user_password(user_name, db)) != NULL) {
			if(strcmp(password, client_message) == 0) {

				if(db_get_online_user_socket(user_name, db) == -1)
					db_add_user_to_online(user_name, sock, db);

				client_message = clear_client_message(client_message);
				send(sock, "@TRUE", strlen("@TRUE"), 0);
				return user_name;
			}
		}
	}
	send(sock, "@RETRY", strlen("@RETRY"), 0);
	return NULL;
}
