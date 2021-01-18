#include "Chat.h"

void db_open(char* path, sqlite3** db) {
    int rc = sqlite3_open(path, db);
    if (rc) fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else fprintf(stdout, "Database [%s] opened successfully\n", path);
}

char *db_get_user_password(char *login, sqlite3* db){
    char *password = NULL;
    sqlite3_stmt *result;
    char* statement = "select password from users where login='";
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "'");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return false;
    } 

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
      password = strdup((char*)sqlite3_column_text(result, 0));
    }

    sqlite3_finalize(result);
    free(statement);
    return password;
}

