#include "../inc/Chat.h"

static void fill_chat_array(){
    char *s_message = clear_client_message(NULL);

    for(int i = 0; i < user_data.amount_of_chat; i++){
        user_data.chat_array[i].msg_list = NULL;
        user_data.chat_array[i].count_msg = 0;

	    recv(sock, s_message, 1000, 0);
        send(sock, "@GET", strlen("@GET"), 0);
        user_data.chat_array[i].chat_id = atoi(s_message);
        s_message = clear_client_message(s_message);

        recv(sock, s_message, 1000, 0);
        send(sock, "@GET", strlen("@GET"), 0);
        user_data.chat_array[i].chat_name = strdup(s_message);
        s_message = clear_client_message(s_message);

        recv(sock, s_message, 1000, 0);
        send(sock, "@GET", strlen("@GET"), 0);
        user_data.chat_array[i].count_users = atoi(s_message);
        s_message = clear_client_message(s_message);

        user_data.chat_array[i].image_path = strdup("resource/images/sh.jpg"); //later 
        //user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, int_to_str(i+1));
        //user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, ".png");

        recv(sock, s_message, 1000, 0);
        send(sock, mx_itoa(user_data.chat_array[i].count_users), strlen(mx_itoa(user_data.chat_array[i].count_users)), 0);
        s_message = clear_client_message(s_message);

        user_data.chat_array[i].users_list = (t_foreign_user *)malloc(sizeof(t_foreign_user) * user_data.chat_array[i].count_users);
        for(int j = 0; j < user_data.chat_array[i].count_users; j++){

            recv(sock, s_message, 1000, 0);
            send(sock, "@GET", strlen("@GET"), 0);
            user_data.chat_array[i].users_list[j].user_id = atoi(s_message);
            s_message = clear_client_message(s_message);

            recv(sock, s_message, 1000, 0);
            send(sock, "@GET", strlen("@GET"), 0);
            user_data.chat_array[i].users_list[j].login = strdup(s_message);
            s_message = clear_client_message(s_message);

            recv(sock, s_message, 1000, 0);
            send(sock, "@GET", strlen("@GET"), 0);
            user_data.chat_array[i].users_list[j].name = strdup(s_message);
            s_message = clear_client_message(s_message);

            recv(sock, s_message, 1000, 0);
            send(sock, "@GET", strlen("@GET"), 0);
            user_data.chat_array[i].users_list[j].image_path = strdup(s_message);
            s_message = clear_client_message(s_message);
        }
    }
}

void load_data_for_user() {
    char *s_message = clear_client_message(NULL);

    send(sock, "@synchronization", strlen("@synchronization"), 0);
    recv(sock, s_message, 2000, 0);
    s_message = clear_client_message(s_message);

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.user_id = atoi(s_message);
    s_message = clear_client_message(s_message);

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.name = strdup(s_message);
    s_message = clear_client_message(s_message);

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.image_path = strdup(s_message);
    s_message = clear_client_message(s_message);
    
    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.amount_of_chat = atoi(s_message);
    s_message = clear_client_message(s_message);

    user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * 150);
    fill_chat_array();
}
