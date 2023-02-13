#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "mysql_fnct.h"

#define CONFIG_FILE ".mysql_options"
#define GROUP_NAME "client"

MYSQL *connect_to_db() {
  MYSQL *conn = mysql_init(NULL);
  if (conn == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    return NULL;
  }
  
  mysql_options(conn, MYSQL_READ_DEFAULT_GROUP, GROUP_NAME);
  mysql_options(conn, MYSQL_READ_DEFAULT_FILE, CONFIG_FILE);
  
  if (!mysql_real_connect(conn, NULL, NULL, NULL, NULL, 0, NULL, 0)) {
    fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return NULL;
  }
  
  return conn;
}

void close_db_connection(MYSQL *conn) {
  mysql_close(conn);
}

int query(MYSQL *conn, const char *sql) {
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    return 1;
  }
  return 0;
}

int insert(MYSQL *conn, const char *sql) {
  return query(conn, sql);
}

int update(MYSQL *conn, const char *sql) {
  return query(conn, sql);
}

int delete(MYSQL *conn, const char *sql) {
  return query(conn, sql);
}
