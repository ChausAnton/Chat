#include "Chat.h"


char *mx_registration(int sock) {
    char *client_message = clear_client_message(NULL);

    int read_size;

                client_message = clear_client_message(client_message);
                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                    send(sock, "@GET", strlen("@GET"), 0);
                    char *user_name = strdup(client_message);
                    client_message = clear_client_message(client_message);

                    
                        if( db_get_user_password(user_name, db) == NULL ) {
                                char *pass1;
                                char *pass2;

                                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                                    send(sock, "@GET", strlen("@GET"), 0);
                                    pass1 = strdup(client_message);
                                    client_message = clear_client_message(client_message);
                                }

                                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                                    pass2 = strdup(client_message);
                                    client_message = clear_client_message(client_message);
                                }

                                if(strcmp(pass1, pass2) == 0) {
                                    send(sock, "@TRUE", strlen("@TRUE"), 0);
                                    db_add_user(user_name, pass1);
                                    free(pass1);
                                    free(pass2);
                                    db_add_user_to_online(user_name, sock, db);
                                    mx_printerr("dyra zaregalas\n");
                                    return strdup(user_name);
                                }
                                else {
                                    send(sock, "@RETRY", strlen("@RETRY"), 0);
                                    free(pass1);
                                    free(pass2);
                                    return NULL;
                                }
                        }
                }

                recv(sock , client_message , 2000 , 0);
                send(sock, "@GET", strlen("@GET"), 0);
                recv(sock , client_message , 2000 , 0);
                send(sock, "@RETRY", strlen("@RETRY"), 0);
                free(client_message);
    return NULL;
}
