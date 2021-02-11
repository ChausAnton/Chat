#include "../inc/Chat.h"

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
        char *s_message = clear_client_message(NULL);
        send(sock_to, "@message_read", strlen("@message_read"), 0);
        recv(sock_to, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        send(sock_to, thread_info, strlen(thread_info), 0);
        recv(sock_to, s_message, 1000, 0);
        s_message = clear_client_message(s_message);

        int user_num = user_data.chat_array[main_data.main_box.search_chat_index].count_msg;
        send(sock_to, mx_itoa(user_num), strlen(mx_itoa(user_num)),0);

        recv(sock_to, s_message, 1000, 0);
        int server_num = atoi(s_message);

        mx_printerr(mx_itoa(server_num));
        mx_printerr("\n");
}

void *reader() {
	int sock_to;
	sock_work(&sock_to);
    while(thread_info == NULL) {};
    display_loaded_messages();
    sign_in_thread(sock_to);

    while(1) {
        main_reader(sock_to);
    }

    
}
