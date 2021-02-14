#include "Chat.h"

char *mx_registration(int sock) {
    char *user_name;  
	char *password1;
    char *password2;
	int read_size;
    char *client_message = clear_client_message(NULL);
    client_message = clear_client_message(client_message);
    recv(sock , client_message , 2000 , 0);
    if (strcmp(strdup(client_message), "Empty") == 0) {
		send(sock, "Empty back", strlen("Empty back"), 0);
		client_message = clear_client_message(client_message);
		return NULL;
	}
    else if (strcmp(strdup(client_message), "Match") == 0) {
        send(sock, "Match back", strlen("Match back"), 0);
		client_message = clear_client_message(client_message);
		return NULL;
    }
	else {
        send(sock, "Nice back", strlen("Nice back"), 0);
        client_message = clear_client_message(client_message);

        if ((read_size = recv(sock , client_message , 2000 , 0) > 0) &&
        (db_get_user_id(strdup(client_message), db)) == -1) {
            user_name = strdup(client_message);
            client_message = clear_client_message(client_message);
            send(sock, "Name back", strlen("Name back"), 0);

            if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                send(sock, "Pass1 back", strlen("Pass1 back"), 0);
                password1 = strdup(client_message);
                client_message = clear_client_message(client_message);
            }
            else {
                send(sock, "Pass1 error back", strlen("Pass1 error back"), 0);
                return NULL;
            }

            if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                send(sock, "@TRUE", strlen("@TRUE"), 0);
                password2 = strdup(client_message);
                client_message = clear_client_message(client_message);
            }
            else {
                send(sock, "Pass2 error back", strlen("Pass2 error back"), 0);
                return NULL;
            }

            db_add_user(user_name, password1);
            db_add_user_to_online(user_name, sock, db);
            return user_name;
        }
        else {
            send(sock, "Name error back", strlen("Name error back"), 0);
            return NULL;
        }
    }
    return NULL;
}
