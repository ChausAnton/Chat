#include "Chat.h"

static void fill_chat_array(){
    for(int i = 0; i < 20; i++){
        user_data.chat_array[i].chat_id = i;
        user_data.chat_array[i].chat_name = strdup("Chat N");
        user_data.chat_array[i].chat_name = mx_strjoin(user_data.chat_array[i].chat_name, int_to_str(i+1));
        if(i % 2 == 0) user_data.chat_array[i].count_users = 2;
        else user_data.chat_array[i].count_users = i;
        user_data.chat_array[i].image_path = strdup("resource/images/stickers/");
        user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, int_to_str(i+1));
        user_data.chat_array[i].image_path =  mx_strjoin(user_data.chat_array[i].image_path, ".png");
        //user_data.chat_array[i].users_id = (char **)malloc( sizeof(char *) * user_data.chat_array[i].count_users);
    }
}

void load_data_for_user() {
    //user_data.user_id = get_user_id(user_data.login);
    //user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * get_count_of_chats(user_data.login));
    //fill_chat_array(user_data.login, locale_db, user_data.chat_array);
    user_data.chat_array = (t_chat_list *)malloc(sizeof(t_chat_list) * 20);
    fill_chat_array();
}
