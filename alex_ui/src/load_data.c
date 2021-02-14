#include "Chat.h"

static void fill_chat_array(){
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
    //user_data.user_id = get_user_id(user_data.login);
    //user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * get_count_of_chats(user_data.login));
    //fill_chat_array(user_data.login, locale_db, user_data.chat_array);
    user_data.image_path = strdup("resource/images/anonymous.png");
    user_data.amount_of_chat = 20;
    user_data.total_chats = user_data.amount_of_chat;
    user_data.name = strdup(user_data.login);
    user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * 150);
    fill_chat_array();
}
