#include "Chat.h"



void db_add_user(char *login, char *password) {
    char* statement = strdup("insert into users (login, password, name, user_image) values ('");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, password);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, NULL);
    statement = mx_strjoin(statement, "', '");
    statement = mx_strjoin(statement, NULL);
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

void db_set_user_password(char *login, char *new_pass) {
    char* statement = strdup("update users set password='");
    statement = mx_strjoin(statement, new_pass);
    statement = mx_strjoin(statement, "' where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");

    db_exec(statement, db);
    free(statement);
}

void db_set_user_login(char *login, char *new_login) {
    char* statement = strdup("update users set login='");
    statement = mx_strjoin(statement, new_login);
    statement = mx_strjoin(statement, "' where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");

    db_exec(statement, db);
    free(statement);
}

void db_set_user_name(char *login, char *new_name) {
    char* statement = strdup("update users set name='");
    statement = mx_strjoin(statement, new_name);
    statement = mx_strjoin(statement, "' where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");

    db_exec(statement, db);
    free(statement);
}

char *db_get_user_password(char *login, sqlite3* db){
    char *password = NULL;
    sqlite3_stmt *result;
    char* statement = strdup("select password from users where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");
	
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
    char* statement = strdup("select id from users where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");

    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 

    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        user_id = sqlite3_column_int(result, 0);
    }

    sqlite3_finalize(result);
    free(statement);
    return user_id;
}

int db_get_count_user(sqlite3* db) {
    int count = -1;
    sqlite3_stmt *result;

    char* statement = strdup("select count(*) from users;");

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

char* db_get_user_name(char *login, sqlite3* db) {
    char *user_name = strdup("\0");
    sqlite3_stmt *result;
    char* statement = strdup("select name from users where login='");
    statement = mx_strjoin(statement, login);
    statement = mx_strjoin(statement, "';");
    mx_printerr(statement);

    mx_printerr("\nBruh1\n");
 
    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    

    mx_printerr("Bruh2\n");

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 

    rc = sqlite3_step(result);

    mx_printerr("Bruh3\n");

    if (rc == SQLITE_ROW) {
        user_name = strdup((char*)sqlite3_column_text(result, 0));
    }

    sqlite3_finalize(result);
    free(statement);

    mx_printerr("Bruh4\n");
    if(db_get_user_id(login, db) == -1){
        return NULL;
    } 
    else if (strlen(user_name) == 0) {
        return strdup(login);
    }
    mx_printerr("Bruh5\n");
    return user_name;
}

/*void get_user_id_and_login()  {
    char* statement = strdup("select id, login, password from users order by id");
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
}*/

/*void get_user_id_and_login() {
    int count = -1;
    sqlite3_stmt *result;

    char* statement = strdup("select login from users order by id;");
    int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        //sqlite3_close(db);
    }
    //count = sqlite3_column_count(result);
    count = db_get_count_user(db);
    printf("%d   \n", count);
    rc = sqlite3_step(result);
    if (rc == SQLITE_ROW) {
        char* tmp = strdup((char *)sqlite3_column_text(result, 0));
        printf("%s   \n", tmp);
    }

    sqlite3_finalize(result);
    free(statement);
    //return count;
}*/
