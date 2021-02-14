#include "Chat.h"

void db_add_msg(int msg_id_in_chat, int chat_id, int user_id, char* date, char* text) {
    char* statement = strdup("INSERT INTO messages (msg_id_in_chat, chat_id, user_id, msg_date, content) VALUES (");
    statement = mx_strjoin(statement, int_to_str(msg_id_in_chat));
    statement = mx_strjoin(statement, ", ");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ", ");
    statement = mx_strjoin(statement, int_to_str(user_id));
    statement = mx_strjoin(statement, ", '");
    statement = mx_strjoin(statement, date);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, text);
    statement = mx_strjoin(statement, "'); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_all_msg_from_chat(int chat_id) {
    char* statement = strdup("DELETE FROM messages WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}

int db_get_count_msg_for_chat(int chat_id, sqlite3* db) {
    char* statement = strdup("SELECT COUNT(msg_id) FROM messages WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    int count = 0;
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

char** get_all_msg_for_chat(int chat_id, sqlite3* db) {
    char* statement = strdup("select * from messages where chat_id=");
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
    char** result = (char **)malloc(sizeof(char *)*(num_rows + 1));
    for(int i = 0; i <= num_rows; i++){
        result[i] = (char *)malloc(sizeof(char)*(num_cols));
    }
    int index = 0;
    int cnt = 0;
    for(int i = 0; i < num_cols*num_rows; i++){
        result[index] = mx_strjoin(result[index], tmp[i+num_cols]);
        result[index] = mx_strjoin(result[index], "#");
        if(cnt >= 5)  {
            index++;
            cnt = 0;
        }
        else cnt++;
    }
    result[++index] = NULL;
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}

char* get_msg_by_global_id(int msg_id, sqlite3* db) {
    char* statement = strdup("select * from messages where msg_id=");
    statement = mx_strjoin(statement, int_to_str(msg_id));
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
    char* result = (char *)malloc(sizeof(char)*(num_cols*num_rows + 1));
    for(int i = 0; i < num_cols*num_rows; i++){
        result = mx_strjoin(result, tmp[i+num_cols]);
        result = mx_strjoin(result, "#");
    }
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}

char* get_msg_by_msg_id_and_chat_id(int msg_id_in_chat, int chat_id, sqlite3* db) {
    char* statement = strdup("select * from messages where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, " and msg_id_in_chat=");
    statement = mx_strjoin(statement, int_to_str(msg_id_in_chat));
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
    char* result = (char *)malloc(sizeof(char)*(num_cols*num_rows + 1));
    for(int i = 0; i < num_cols*num_rows; i++){
        result = mx_strjoin(result, tmp[i+num_cols]);
        result = mx_strjoin(result, "#");
    }
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}

char** get_msg_for_chat_from_the_num(int msg_id_in_chat, int chat_id, sqlite3* db) {
    char* statement = strdup("select * from messages where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, " and msg_id_in_chat > ");
    statement = mx_strjoin(statement, int_to_str(msg_id_in_chat));
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
    char** result = (char **)malloc(sizeof(char *)*(num_rows + 1));
    for(int i = 0; i <= num_rows; i++){
        result[i] = (char *)malloc(sizeof(char)*(num_cols));
    }
    int index = 0;
    int cnt = 0;
    for(int i = 0; i < num_cols*num_rows; i++){
        result[index] = mx_strjoin(result[index], tmp[i+num_cols]);
        result[index] = mx_strjoin(result[index], "#");
        if(cnt >= 5)  {
            index++;
            cnt = 0;
        }
        else cnt++;
    }
    result[++index] = NULL;
    sqlite3_free_table(tmp);
    free(statement);
    return result;
}
