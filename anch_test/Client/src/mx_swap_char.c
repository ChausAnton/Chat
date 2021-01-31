#include "Chat.h"

void mx_swap_char(char *s1, char *s2) {
    char temp = *s1;
    char temp2 = *s2;
    
    *s2 = temp;
    *s1 = temp2;
}
