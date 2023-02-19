#ifndef MYSQL_ROUTE_FNCT_H
#define MYSQL_ROUTE_FNCT_H
#include <glib.h>
#include <mariadb/mysql.h>
#include "struct_route.h"

MYSQL *connect_to_db();
void close_db_connection(MYSQL *conn);
int query(MYSQL *conn, const char *sql);
int insert(MYSQL *conn, const char *sql);
int update(MYSQL *conn, const char *sql);
int delete(MYSQL *conn, const char *sql);
Station getRouteByCode (Route route);
gboolean updateRoute (Route route);
gboolean insertRoute (Route route);
gboolean deleteRoute (Route route);
GList* mysql_get_all_routes(MYSQL *conn);

#endif
