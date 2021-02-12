#include "Chat.h"

void db_open(char* path, sqlite3** db) {
   struct stat buffer;
   int exist = stat("database/uchat.db", &buffer);
   if (exist != 0) {
      db_create();
   } else {
      int rc = sqlite3_open_v2(path, db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX, NULL);
      if (rc) fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
      else fprintf(stdout, "Database [%s] opened successfully\n", path);
   }
}

static int callback(void *data, int argc, char **argv, char **azColName){
   if(data)
   for(int i = 0; i < argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

void db_exec(char* statement, sqlite3* db) {
   char* zErrMsg = NULL;
   int rc = sqlite3_exec(db, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      exit(EXIT_FAILURE);
   } 
} 

void db_create() {
   mkdir("database", S_IRWXU | S_IRWXG | S_IRWXO);
   //int rc = sqlite3_open("database/uchat.db", &db);
   sqlite3_open_v2("database/uchat.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);
   char *sql = NULL;
   sql = mx_strjoin(sql, "PRAGMA encoding = \"UTF-8\";");
   sql = mx_strjoin(sql, "CREATE TABLE IF NOT EXISTS `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT not null, `login` varchar(30) UNIQUE not null, `password` varchar(30) not null, `name` varchar(50) null, `user_image` varchar(1000) NULL);");
   sql = mx_strjoin(sql, "CREATE TABLE IF NOT EXISTS `chats` ( `chat_id` INTEGER PRIMARY KEY AUTOINCREMENT , `member_count` INT(5) NOT NULL DEFAULT 2, `chat_name` varchar(30) NULL, `chat_image` varchar(1000) NULL);");
   sql = mx_strjoin(sql, "CREATE TABLE IF NOT EXISTS `members` ( `member_id` INTEGER PRIMARY KEY AUTOINCREMENT, `chat_id` INTEGER NOT NULL, `user_id` INTEGER NOT NULL);");
   sql = mx_strjoin(sql, "CREATE TABLE IF NOT EXISTS `messages` ( `msg_id` INTEGER PRIMARY KEY AUTOINCREMENT, `msg_id_in_chat` INTEGER not null, `chat_id` INTEGER NOT NULL, `user_id` INTEGER NOT NULL, `msg_date` TEXT NOT NULL , `content` TEXT NOT NULL);");
   sql = mx_strjoin(sql, "CREATE TABLE IF NOT EXISTS `online_users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `online_user_id` INTEGER NOT NULL, `socket` INTEGER UNIQUE NOT NULL);");
   
   db_exec(sql, db);

   free(sql);
}

void db_close(sqlite3* db) {
   sqlite3_close(db);
}
