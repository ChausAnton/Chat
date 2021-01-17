#include "Chat.h"

void open_db(char* path, sqlite3** db) {
    int rc = sqlite3_open(path, db);
    if (rc) fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else fprintf(stdout, "Database [%s] opened successfully\n", path);
}

void get_user_password(char *login, sqlite3* db){
    
}
