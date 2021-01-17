#include "Chat.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }

    int length1 = 0;
    if(s1 != NULL) {
        length1 = strlen(s1);
    }

    int length2 = 0;
    if(s2 != NULL) {
        length2 = strlen(s2);
    }

    char *str = mx_strnew(length1 + length2);
    if (str == NULL) {
        return NULL;
    }

    if(s1 != NULL)
        mx_strcat(str, s1);
    if(s2 != NULL)
        mx_strcat(str, s2);
    return str;

}
