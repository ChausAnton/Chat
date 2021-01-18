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

int mx_strlen(const char *s) {
    int j = 0;
    char i = s[0];
    while(i != '\0') {
        j++;
        i = s[j];
    }
    return j;
}

char *mx_strnew(const int size) {

    char *str = (char*) malloc((size + 1) * sizeof(char));

    if (str == NULL || size < 0) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
    str[size] = '\0';
    return str;
}

char* int_to_str(int num) {
   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}
