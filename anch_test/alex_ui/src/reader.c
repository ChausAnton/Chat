#include "../inc/Chat.h"
int check;
int user_num;

void sign_in_thread(int sock_to) {
    char *s_message = clear_client_message(NULL);

    send(sock_to, "@sign_in", strlen("@sign_in"), 0);
    recv(sock_to, s_message, 2000, 0);

    s_message = clear_client_message(s_message);
    send(sock_to, user_data.login, strlen(user_data.login), 0);
    recv(sock_to, s_message, 2000, 0);
    s_message = clear_client_message(s_message);
    send(sock_to, user_data.password, strlen(user_data.password), 0);
    recv(sock_to, s_message, 2000, 0);
    //mx_printerr(s_message);

    free(s_message);
}

void main_reader(int sock_to) {
    for(int j = 0; j < user_data.amount_of_chat; j++) {
        check = user_data.chat_array[j].chat_id;
        user_num = user_data.chat_array[j].count_msg;

        if(barashka == true) {

            char *s_message = clear_client_message(NULL);
            send(sock_to, "@message_read", strlen("@message_read"), 0);
            recv(sock_to, s_message, 1000, 0);
            s_message = clear_client_message(s_message);

            send(sock_to, mx_itoa(check), strlen(mx_itoa(check)), 0);
            recv(sock_to, s_message, 1000, 0);
            s_message = clear_client_message(s_message);

            send(sock_to, mx_itoa(user_num), strlen(mx_itoa(user_num)),0);
            recv(sock_to, s_message, 1000, 0);
            int server_num = atoi(s_message);
            s_message = clear_client_message(s_message);

            int messages_num = 0;
            if(user_num < server_num) {
                user_data.chat_array[j].count_msg = server_num;
                messages_num = server_num - user_num;
            }

            if(user_data.chat_array[j].msg_list == NULL){
                user_data.chat_array[j].msg_list = (t_message *)malloc(sizeof(t_message) * 30000);
            }

            for(int i = 0; i < messages_num; i++) {
                send(sock_to, "@message_size", strlen("@message_size"), 0);
                recv(sock_to, s_message, 1000, 0);
                int message_size = atoi(s_message);
                s_message = clear_client_message(s_message);

                char *message_user = (char *) malloc(sizeof(char) * message_size + 1);
                message_user[message_size] = '\0';
                send(sock_to, "@message_user", strlen("@message_user"), 0);
                recv(sock_to, message_user, message_size, 0);

                if(i == messages_num - 1) { 
                    load_messages_for_chat(check, user_num + i, message_user, 1);
                } else {
                    load_messages_for_chat(check, user_num + i, message_user, 0);
                }
                
                free(message_user);
            }
        }
    }
}

void read_new_chats(int sock_to) {
    if(barashka == true) {
        char *s_message = clear_client_message(NULL);
        send(sock_to, "@new_chat_from_server", strlen("@new_chat_from_server"), 0);
        recv(sock_to, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock_to, mx_itoa(user_data.user_id), strlen(mx_itoa(user_data.user_id)), 0);
        recv(sock_to, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock_to, mx_itoa(user_data.amount_of_chat), strlen(mx_itoa(user_data.amount_of_chat)), 0);
        recv(sock_to, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock_to, "@server_chats_num", strlen("@server_chats_num"), 0);
        recv(sock_to, s_message, 1000, 0);
        int server_chats_num = atoi(s_message);
        s_message = clear_client_message(s_message);

        int new_chats_num = server_chats_num - user_data.amount_of_chat;
        for(int i = 0; i < new_chats_num; i++) {
            send(sock_to, "@chat_id", strlen("@chat_id"), 0);
            recv(sock_to, s_message, 1000, 0);

            add_new_chat_from_server(atoi(s_message), sock_to);

            s_message = clear_client_message(s_message);
        }

        if(new_chats_num < 0) {
            new_chats_num = new_chats_num * -1;
            char **all_server_chat_id = (char **) malloc(sizeof(char *) * (server_chats_num + 1));
            all_server_chat_id[server_chats_num] = NULL;
            for(int i = 0; i < server_chats_num; i++) {
                send(sock_to, "@chat_id", strlen("@chat_id"), 0);
                recv(sock_to, s_message, 1000, 0);
                all_server_chat_id[i] = strdup(s_message);

                s_message = clear_client_message(s_message);
            }
            delete_chat_from_server(all_server_chat_id);
        }

    }
}

void mx_reconect(int *sock_to) {
    struct sockaddr_in server;
	struct hostent *serv;
    close(*sock_to);
	
	//Create socket
	*sock_to = socket(AF_INET , SOCK_STREAM , 0);
	if (*sock_to == -1)
	{
		printf("Could not create socket");
	}
	//puts("Socket created");

	serv = gethostbyname(ip);
    memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	memcpy(&server.sin_addr.s_addr, serv->h_addr_list[0],  serv->h_length);
	server.sin_port = htons(serverport);
	//Connect to remote server
    while (connect(*sock_to, (struct sockaddr *)&server, sizeof(server)) == -1) {
        //play_music();
        close(*sock_to);
        *sock_to = socket(AF_INET, SOCK_STREAM, 0);
        usleep(100000);
    }
    //mx_printerr("reconnect!!!\n");
}

void read_new_chat_name(int sock_to) {
    if(barashka == true) {
        char *s_message = clear_client_message(NULL);

        send(sock_to, "@read_new_chat_name", strlen("@read_new_chat_name"), 0);
        recv(sock_to, s_message, 1000, 0);

        s_message = clear_client_message(s_message);

        send(sock_to, mx_itoa(user_data.user_id), strlen(mx_itoa(user_data.user_id)), 0);
        recv(sock_to, s_message, 1000, 0);

        s_message = clear_client_message(s_message);

        send(sock_to, mx_itoa(user_data.amount_of_chat), strlen(mx_itoa(user_data.amount_of_chat)), 0);
        recv(sock_to, s_message, 1000, 0);

        s_message = clear_client_message(s_message);

        send(sock_to, "@server_chats_num", strlen("@server_chats_num"), 0);
        recv(sock_to, s_message, 1000, 0);
        int server_chats_num = atoi(s_message);

        s_message = clear_client_message(s_message);

        if(server_chats_num == user_data.amount_of_chat) {
            for(int i = 0; i < server_chats_num; i++) {
                send(sock_to, "@chat_id", strlen("@chat_id"), 0);
                recv(sock_to, s_message, 1000, 0);
                int chat_id = atoi(s_message);

                s_message = clear_client_message(s_message);

                send(sock_to, "@chat_name", strlen("@chat_name"), 0);
                recv(sock_to, s_message, 1000, 0);

                update_chat_name(chat_id, s_message);

                s_message = clear_client_message(s_message);
            }
        }

    }
}

void read_new_user(int sock_to) {
     for(int j = 0; j < user_data.amount_of_chat; j++) {
        int chat_id = user_data.chat_array[j].chat_id;

        if(barashka == true) {

            char *s_message = clear_client_message(NULL);
            send(sock_to, "@read_new_user", strlen("@read_new_user"), 0);
            recv(sock_to, s_message, 1000, 0);
            s_message = clear_client_message(s_message);

            send(sock_to, mx_itoa(chat_id), strlen(mx_itoa(chat_id)), 0);
            recv(sock_to, s_message, 1000, 0);
            s_message = clear_client_message(s_message);

            send(sock_to, "@user_num", strlen("@user_num"),0);
            recv(sock_to, s_message, 1000, 0);
            int server_num = atoi(s_message);
            s_message = clear_client_message(s_message);

            
            for(int i = 0; i < server_num; i++) {
                send(sock_to, "@user_id", strlen("@user_id"),0);
                recv(sock_to, s_message, 1000, 0);
                int user_id = atoi(s_message);
                s_message = clear_client_message(s_message);

                add_new_user_from_server(chat_id, user_id, i, sock_to);
            }
        }
    }
    new_user = false;
}

void *reader() {
	int sock_to;
	sock_work(&sock_to);
    int exit_code = 1;
    while(thread_info == NULL && exit_thread != true) {};     
    if(exit_thread == true) pthread_exit(&exit_code);

    while(1) {
        if (thread_info != NULL) {
            if(atoi(thread_info) > 0) {
                main_reader(sock_to);
                if(new_user == true)
                    read_new_user(sock_to);
            }
            read_new_chats(sock_to);
            read_new_chat_name(sock_to);

            char *s_message = clear_client_message(NULL);
            s_message = clear_client_message(s_message);
            
        }
        if(exit_thread == true) {
            char *s_message = clear_client_message(NULL);
            send(sock_to, "@exit_thread", strlen("@exit_thread"), 0);
            recv(sock_to, s_message, 1000, 0);
            free(s_message);
            pthread_exit(&exit_code);
        }
    }


    return 0;
}
