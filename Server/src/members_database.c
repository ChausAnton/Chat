#include "Chat.h"

void db_add_member(int chat_id, int user_id) {
    char* statement = strdup("INSERT INTO members (chat_id, user_id) VALUES (");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ", ");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, "); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_member(int chat_id, int user_id) {
    char* statement = strdup("DELETE FROM members WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, "AND user_id=");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}

void db_del_all_member_for_chat(int chat_id) {
    char* statement = strdup("DELETE FROM members WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}

char** get_all_user_id_for_chat(int chat_id)  {
    char* statement = strdup("select user_id from members where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    char** tmp = NULL;
    int num_rows, num_cols;
    char* zErrMsg = NULL;
    int rc = sqlite3_get_table(db, statement, &tmp, &num_rows, &num_cols, &zErrMsg);
    if( rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       exit(EXIT_FAILURE);
    } 
    char** result = (char **)malloc(sizeof(char *)*(num_cols*num_rows));
    for(int i = 0; i < num_cols*num_rows; i++){
        //if(i%num_cols == 0) printf("%s\n", "");
        //printf("%s   ", result[i]);
        result[i] = strdup(tmp[i+num_cols]);
        //printf("%s   ", result[i]);
    }
    //printf("%s\n", "");
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}

char** get_all_chat_id_for_user(int user_id, sqlite3* db)  {
    char* statement = strdup("select chat_id from members where user_id=");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ";");

    char** tmp = NULL;
    int num_rows, num_cols;
    char* zErrMsg = NULL;
    int rc = sqlite3_get_table(db, statement, &tmp, &num_rows, &num_cols, &zErrMsg);
    if( rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       exit(EXIT_FAILURE);
    } 
    char** result = (char **)malloc(sizeof(char *)*(num_cols*num_rows)+1);
    for(int i = 0; i < num_cols*num_rows; i++){
        result[i] = strdup(tmp[i+num_cols]);
    }
    result[num_cols*num_rows] = NULL;
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}

int get_count_chat_id_for_user(int user_id, sqlite3* db)  {
    char* statement = strdup("select count(chat_id) from members where user_id=");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ";");
    
    int count = -1;
    sqlite3_stmt *result;
    
    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(result, 0);
    }

    sqlite3_finalize(result);
    free(statement);
    return count;
}
