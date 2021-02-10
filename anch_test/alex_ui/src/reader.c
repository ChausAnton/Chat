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


void *reader() {
	int sock_to;
	sock_work(&sock_to);
    sign_in_thread(sock_to);

    display_loaded_messages();

	while(1) {
        mx_printerr("!!!!!!!!!!\n");
        char *s_message = clear_client_message(NULL);
        send(sock_to, "@message_read", strlen("@message_read"), 0);
        recv(sock_to, s_message, 2000, 0);
        s_message = clear_client_message(s_message);
        mx_printerr("@@@@@@@@@@@@@@@@@@\n");

        recv(sock_to, s_message, 2000, 0);
        send(sock_to, "@GET", strlen("@GET"), 0);
        int s_count = atoi(s_message);
        s_message = clear_client_message(s_message);
        mx_printerr("***************\n");

        int count = user_data.chat_array[main_data.main_box.search_chat_index].count_msg;
        mx_printerr("\nbadum: ");
        mx_printerr( mx_itoa(count));
        mx_printerr("\n\n");

        send(sock_to, mx_itoa(count), strlen(mx_itoa(count)), 0);
        recv(sock_to, s_message, 2000, 0);
        s_message = clear_client_message(s_message);

        if(count != s_count) {
            user_data.chat_array[main_data.main_box.search_chat_index].count_msg = s_count;
        }

        int messages_num = s_count - count;
	    if (messages_num < 0) {
		    messages_num = messages_num * -1;
	    }

        if(user_data.chat_array[main_data.main_box.search_chat_index].msg_list == NULL){
            user_data.chat_array[main_data.main_box.search_chat_index].msg_list = (t_message *)malloc(sizeof(t_message) * 30000);
        } else {
            mx_printerr("Bruh!!!!!2\n");
        }
        
		for(int i = 0; i < messages_num; i++) {
            
            recv(sock_to, s_message, 2000, 0);
            send(sock_to, "@GET", strlen("@GET"), 0);
            int size = atoi(s_message);
            s_message = clear_client_message(s_message);

            char *get_message = (char *) malloc(sizeof(char) * (size + 1));
            get_message[size] = '\0';
            recv(sock_to, get_message, size, 0);
            send(sock_to, "@GET", strlen("@GET"), 0);

            mx_printerr(get_message);
            load_messages_for_chat(count + i, get_message);
            gtk_widget_hide(main_data.main_box.right_chat_box);
            gtk_widget_show_all(main_data.main_box.right_chat_box);

            free(get_message);
        }
        //rend essage
	}
}
