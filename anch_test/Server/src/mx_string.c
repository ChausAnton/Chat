#include "Chat.h"
void mx_printerr(const char *s) {
     int len = strlen(s);
     write(2, s, len);
}

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

char *clear_client_message(char *client_message){
	if(client_message != NULL) {
		free(client_message);
	}

	char *message = malloc(2000 * sizeof(char));
	for(int i = 0; i < 2000; i++)
		message[i] = '\0';
	return message;
}

int mx_count_words(const char *str, char c) {
    int count = 0;
    bool was_c = true;
    if (str == NULL) return -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c && str[i + 1] != '\0')
            was_c = true;
        else if (was_c == true) {
            was_c = false;
            count++;
        }        
    }
    return count;
}


char *mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;
    while (src[i] != '\0') {
        if (i == len) {
            return (char *) dst;
        }
        dst[i] = src[i];
        i++;
    }
    return (char *) dst;
}

char *mx_strndup(const char *s1, size_t n) {
    size_t lenght = strlen(s1);
    if(n < lenght) lenght = n;
    char *DupStr = mx_strnew(lenght);
    if(DupStr == NULL) {
        return NULL;
    }
    return mx_strncpy(DupStr, s1, lenght);
}

char **mx_strsplit(char const *s, char c) {
    if (s == NULL) return NULL;
    int length = 0;
    int i = 0;
    char **arr = (char **) malloc((mx_count_words(s, c) + 1) * sizeof(char *));
    while((*s) && (*s != '\0')) {
        if(*s != c) {
            length = 0;
            while (s[length] != c && s[length]) {
                length++;
            }
            arr[i] = mx_strndup(s, length);
            s += length;
            i++;
            continue;
        }
        s++;
    }
    arr[i] = NULL;
    return arr;
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
    while (num != 0)
    {
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
