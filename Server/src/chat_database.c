#include "Chat.h"

void db_add_chat(int count, char* name) {
    char* statement = strdup("INSERT INTO chats (member_count, chat_name) VALUES (");
    statement = mx_strjoin(statement, int_to_str(count));
    statement = mx_strjoin(statement, ", '");
    statement = mx_strjoin(statement, name);
    statement = mx_strjoin(statement, "'); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_chat(int chat_id) {
    char* statement = strdup("DELETE FROM chats WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");
    
    db_del_all_member_for_chat(chat_id);
    db_del_all_msg_from_chat(chat_id);
    db_exec(statement, db);
    free(statement);
}

int db_get_last_chat_id() {
    int last_chat_id = -1;
    sqlite3_stmt *result;
    char* statement = strdup("SELECT MAX(chat_id) FROM chats");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return false;
    }
    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
      char* tmp = strdup((char*)sqlite3_column_text(result, 0));
      last_chat_id = atoi(tmp);
      free(tmp);
    }
   
    sqlite3_finalize(result);
    free(statement);
    return last_chat_id;
}

char* db_get_chat_name(int chat_id, sqlite3* db) {
    char *chat_name = NULL;
    sqlite3_stmt *result;
    char* statement = "select chat_name from chats where chat_id=";
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, "");
 
    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 

    rc = sqlite3_step(result);

    if (rc == SQLITE_ROW) {
        chat_name = strdup((char*)sqlite3_column_text(result, 0));
    }

    sqlite3_finalize(result);
    free(statement);
    return chat_name;
}

int get_count_users_for_chat(int chat_id, sqlite3* db)  {
    char* statement = strdup("select member_count from members where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
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
