#include "Chat.h"

void db_open(char* path, sqlite3** db) {
    int rc = sqlite3_open(path, db);
    if (rc) fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else fprintf(stdout, "Database [%s] opened successfully\n", path);
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i < argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

void db_exec(char* statement, sqlite3* db) {
   char* zErrMsg = NULL; //For printing erro if we find it
   int rc = sqlite3_exec(db, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
} 
