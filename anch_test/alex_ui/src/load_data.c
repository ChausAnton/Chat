#include "Chat.h"

static void fill_chat_array(){
    char *s_message = clear_client_message(NULL);

    for(int i = 0; i < user_data.amount_of_chat; i++){
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

        user_data.chat_array[i].image_path = strdup("resource/images/stickers/");//later 
        user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, int_to_str(i+1));
        user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, ".png");
        //user_data.chat_array[i].users_id = (char **)malloc( sizeof(char *) * user_data.chat_array[i].count_users);
    }
}

void load_data_for_user() {
    char *s_message = clear_client_message(NULL);

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.user_id = atoi(s_message);
    s_message = clear_client_message(s_message);

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.name = strdup(s_message);
    s_message = clear_client_message(s_message);
    
    user_data.image_path = strdup("resource/images/anonymous.png");

    recv(sock, s_message, 2000, 0);
    send(sock, "@GET", strlen("@GET"), 0);
    user_data.amount_of_chat = atoi(s_message);
    s_message = clear_client_message(s_message);

    user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * 150);
    fill_chat_array();
}
