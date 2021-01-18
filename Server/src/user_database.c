#include "Chat.h"

void db_add_user(char *login, char *password, char *name) {
    char* statement = strdup("insert into users (login, password, name) values ('");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, password);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, name);
    statement = mx_strjoin(statement, "'); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_user(char *login) {
    char* statement = strdup("delete from users where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");

    db_exec(statement, db);
    free(statement);
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
