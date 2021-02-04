#include "Chat.h"

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

void mx_swap_char(char *s1, char *s2) {
    char temp = *s1;
    char temp2 = *s2;
    
    *s2 = temp;
    *s1 = temp2;
}

void mx_str_reverse(char *s) {
    int len = strlen(s);
    
    for (int i = 0; i < len/2; i++) {
        mx_swap_char(&s[i], &s[len - 1 - i]);
    }
}

char *mx_itoa(int number) {
    int lenght = 0;
    unsigned int num = number;
    while (num != 0) {
        num = num / 10;
        lenght++;
    }
    
    char *arr = NULL;
    arr = mx_strnew(lenght);
    bool min = false;
    num = number;
    int i = 0;
    if (number == 0) return strcpy(arr, "0");

    if (number < 0) {
        min = true;
        num = num * -1;
    } 
    
    while(num != 0) {
        arr[i] = (num % 10) + 48;
        num = num / 10;
        i++;
    }
    if(min == true) arr[i] = '-';
    mx_str_reverse(arr);
    return arr;
}
char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)  return NULL;
    else if (s1 == NULL) return strdup(s2);
    else if (s2 == NULL)  return strdup(s1);
    else {
        int ns1 = strlen(s1), ns2 = strlen(s2);
        char *new = mx_strnew(ns1 + ns2);

        new = strcpy(new, s1);
        new = strcat(new, s2);
        return new;
    }
}

char *int_to_str(int num) {

   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}
