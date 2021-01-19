#include "Chat.h"

void db_add_member(int chat_id, int user_id) {
    char* statement = strdup("INSERT INTO members (chat_id, users_id) VALUES (");
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
    statement = mx_strjoin(statement, "AND users_id=");
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