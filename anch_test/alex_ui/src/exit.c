#include "Chat.h"

void exit_client() {
    send(sock, "@exit_client", strlen("@exit_client"), 0);
    gtk_main_quit();
}
