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
    } 

    rc = sqlite3_step(result);

    if (rc == SQLITE_ROW) {
        password = strdup((char*)sqlite3_column_text(result, 0));
    }

    sqlite3_finalize(result);
    free(statement);
    return password;
}

int db_get_user_id(char *login, sqlite3* db) {
    int user_id = -1;
    sqlite3_stmt *result;
    char* statement = "select id from users where login='";
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "'");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        char* tmp = strdup((char*)sqlite3_column_text(result, 0));
        user_id = atoi(tmp);
    }

    sqlite3_finalize(result);
    free(statement);
    return user_id;
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i < argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

void db_exec(char* statement, sqlite3* db) {
   char* zErrMsg = NULL; //For printing erro if we find it
   int rc = sqlite3_exec(db, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
} 

char* int_to_str(int num) {
   int length = snprintf(NULL, 0, "%d", num);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", num);
   return result;
}
