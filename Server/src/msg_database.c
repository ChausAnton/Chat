#include "Chat.h"

void db_add_msg(int chat_id, int user_id, char* date, char* text) {
    char* statement = strdup("INSERT INTO messages (chat_id, user_id, msg_date, content) VALUES (");
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
