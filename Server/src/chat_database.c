#include "Chat.h"

void db_add_chat(int count, char* name, sqlite3* db) {
    char* statement = strdup("INSERT INTO chats (member_count, chat_name, chat_image) VALUES (");
    statement = mx_strjoin(statement, int_to_str(count));
    statement = mx_strjoin(statement, ", '");
    statement = mx_strjoin(statement, name);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, NULL);
    statement = mx_strjoin(statement, "'); ");

    db_exec(statement, db);
    free(statement);
}

void db_del_chat(int chat_id, sqlite3* db) {
    char* statement = strdup("DELETE FROM chats WHERE chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");
    
    db_del_all_member_for_chat(chat_id);
    db_del_all_msg_from_chat(chat_id);
    db_exec(statement, db);
    free(statement);
}

int db_get_last_chat_id(sqlite3* db) {
    int last_chat_id = -1;
    sqlite3_stmt *result;
    char* statement = strdup("SELECT MAX(chat_id) FROM chats;");

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
    char* statement = strdup("select chat_name from chats where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");
 
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

char* db_get_chat_image(int chat_id, sqlite3* db) {
    char *chat_name = NULL;
    sqlite3_stmt *result;
    char* statement = strdup("select chat_image from chats where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");
 
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
    char* statement = strdup("select member_count from chats where chat_id=");
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

void db_set_chat_count(int chat_id, int new_count) {
    char* statement = strdup("update chats set member_count=");
    statement = mx_strjoin(statement, int_to_str(new_count));
    statement = mx_strjoin(statement, " where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}

void db_set_chat_image(int chat_id, char* new_iamge_path, sqlite3* db) {
    char* statement = strdup("update chats set chat_image='");
    statement = mx_strjoin(statement, new_iamge_path);
    statement = mx_strjoin(statement, "' where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}
void db_set_chat_name(int chat_id, char *new_name, sqlite3* db) {
    char* statement = strdup("update chats set chat_name='");
    statement = mx_strjoin(statement, new_name);
    statement = mx_strjoin(statement, "' where chat_id=");
    statement = mx_strjoin(statement, int_to_str(chat_id));
    statement = mx_strjoin(statement, ";");

    db_exec(statement, db);
    free(statement);
}
