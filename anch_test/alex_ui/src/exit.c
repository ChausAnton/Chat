#include "Chat.h"

void exit_client() {
    exit_thread = true;
    int *ptr[1];
    send(sock, "@exit_client", strlen("@exit_client"), 0);
    pthread_join(sniffer_thread, (void**)&(ptr[0]));
    gtk_main_quit();
}
