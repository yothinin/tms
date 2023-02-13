#ifndef MYSQL_FNCT_H
#define MYSQL_FNCT_H

#include <mysql.h>

MYSQL *connect_to_db();
void close_db_connection(MYSQL *conn);
int query(MYSQL *conn, const char *sql);
int insert(MYSQL *conn, const char *sql);
int update(MYSQL *conn, const char *sql);
int delete(MYSQL *conn, const char *sql);

#endif
