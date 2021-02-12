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
    mx_printerr(s_message);

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

                load_messages_for_chat(check, user_num + i, message_user);

                free(message_user);

                if(i == messages_num - 1){
                    while(main_data.main_box.right_chat_box == NULL) {};
                    gtk_widget_hide(main_data.main_box.right_chat_box);
                    gtk_widget_show_all(main_data.main_box.right_chat_box);
                }
            }
        }
    }
}

void *reader() {
	int sock_to;
	sock_work(&sock_to);
    while(thread_info == NULL) {};
    display_loaded_messages();

    while(1) {
        main_reader(sock_to);
        //new_get_chat(sock_to);
        if(exit_thread == true) {
            char *s_message = clear_client_message(NULL);
            send(sock_to, "@exit_thread", strlen("@exit_thread"), 0);
            recv(sock_to, s_message, 1000, 0);
            free(s_message);
            int exit_code = 1;
            pthread_exit(&exit_code);
        }
    }


    return 0;
}
