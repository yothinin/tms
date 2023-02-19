#include <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include "mysql_route_fnct.h"
#include "functions.h"

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

/*
Station getStationNameByCode (Station station){
  MYSQL *conn = connect_to_db ();
  MYSQL_RES *result;
  MYSQL_ROW row;
  // Build the query using the station code
  gchar sql[1000];
  sprintf(sql, "SELECT sta_name FROM station WHERE sta_code='%s'", station.staCode);

  if (query(conn, sql)) {
    fprintf(stderr, "Error: failed to execute query\n");
    close_db_connection(conn);
    exit (1);
  }

  result = mysql_use_result (conn);
 
  if ((row = mysql_fetch_row (result)) != NULL)
    station.staName = g_strdup (row[0]);
  else
    station.staName = NULL;
  
  mysql_free_result(result);
  close_db_connection(conn);

  return station;
}

gboolean updateStationName (Station station){
  MYSQL *conn = connect_to_db();
  gboolean result = FALSE;
  gchar *sql = g_strdup_printf ("UPDATE station SET sta_name = '%s' WHERE sta_code = '%s'", station.staName, station.staCode);
  
  if (query (conn, sql) == 0){
    result = TRUE;
  }else {
    fprintf(stderr, "Error: failed to execute query\n");
    g_free (sql);
    close_db_connection(conn);
    exit (1);
  }
  
  g_free (sql);
  mysql_close (conn);

  return result;
}

gboolean insertStation (Station station) {
  MYSQL *conn = connect_to_db ();
  gboolean result = FALSE;
  
  gchar *sql = g_strdup_printf ("INSERT INTO station (sta_code, sta_name) VALUE ('%s', '%s')", station.staCode, station.staName);
  
  if (query (conn, sql) == 0){
    result = TRUE;
  }else{
    fprintf(stderr, "Error: failed to execute query\n");
    g_free (sql);
    close_db_connection(conn);
    exit (1);
  }
  
  g_free (sql);
  close_db_connection (conn);

  return result;
}

gboolean deleteStation(const gchar *staCode) {
  MYSQL *conn = connect_to_db();
  gboolean result = FALSE;
  gchar *sql = g_strdup_printf("DELETE FROM station WHERE sta_code = '%s'", staCode);

  if (query(conn, sql) == 0) {
    result = TRUE;
  } else {
    gchar *warning_msg = g_strdup_printf("Cannot delete station '%s' because it is used in the route table.", staCode);
    display_warning_message(warning_msg);  // display the warning message
    g_free(warning_msg);
  }

  g_free(sql);
  mysql_close(conn);

  return result;
}
*/

GList* getAllRoutes(MYSQL *conn) {
    gchar *query = "SELECT rou_code, rou_direction, sta_from, sta_to FROM route ORDER BY rou_code, rou_direction";

    if (mysql_query(conn, query) != 0) {
        g_error("mysql_query() failed: %s", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES *res = mysql_use_result(conn);
    if (res == NULL) {
        g_error("mysql_use_result() failed: %s", mysql_error(conn));
        return NULL;
    }

    GList *routeList = NULL;

    while (MYSQL_ROW row = mysql_fetch_row(res)) {
        Route *route = g_new(Route, 1);
        route->rouCode = g_strdup(row[0]);
        route->rouDirection = g_strdup(row[1]);
        route->staFrom = g_strdup(row[2]);
        route->staTo = g_strdup(row[3]);

        routeList = g_list_append(routeList, route);
     }

  mysql_free_result(res);
  
  return routeList;
}

