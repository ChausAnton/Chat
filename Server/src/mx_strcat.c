#include "Chat.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int len_1 = mx_strlen(s1);
    int len_2 = mx_strlen(s2);

    for (int i = 0; i < len_2; i++) {
        s1[len_1 + i] = s2[i];
    }
    s1[len_1 + len_2] = '\0';
    return s1;
}
