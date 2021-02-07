#include "Chat.h"

void mx_printerr(const char *s) {
     int len = strlen(s);
     write(2, s, len);
}
