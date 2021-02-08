#include "Chat.h"

void db_add_user_to_online(char *login, int socket, sqlite3* db){
    int user_id = db_get_user_id(login, db);
    char* statement = strdup("insert into online_users (online_user_id, socket) values (");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ", ");
    statement = mx_strjoin(statement, int_to_str(socket));
    statement = mx_strjoin(statement, "); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_user_from_online(char *login, sqlite3* db){
    int user_id = db_get_user_id(login, db);
    char* statement = strdup("delete from online_users where online_user_id=");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);

    free(statement);
}

int db_get_online_user_socket(char *login, sqlite3* db) {
    int socket = -1;
    sqlite3_stmt *result;

    int user_id = db_get_user_id(login, db);
    char* statement = strdup("select socket from online_users where online_user_id=");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ";");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        char* tmp = strdup((char*)sqlite3_column_text(result, 0));
        socket = atoi(tmp);
    }

    sqlite3_finalize(result);
    free(statement);
    return socket;
}

int db_get_count_online_user(sqlite3* db) {
    int count = -1;
    sqlite3_stmt *result;

    char* statement = strdup("select count(*) from online_users");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        char* tmp = strdup((char*)sqlite3_column_text(result, 0));
        count = atoi(tmp);
    }

    sqlite3_finalize(result);
    free(statement);
    return count;
}
