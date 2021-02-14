#include "Chat.h"

void exit_client() {
    exit_thread = true;
    int *ptr[1];
    pthread_join(sniffer_thread, (void**)&(ptr[0]));
    send(sock, "@exit_client", strlen("@exit_client"), 0);
    gtk_main_quit();
}
