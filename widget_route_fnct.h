/*
 * header for station_widget_fnct.c
 */
 
#ifndef WIDGET_ROUTE_FNCT_H
#define WIDGET_ROUTE_FNCT_H
#include "struct_route.h"
#include "mysql_route_fnct.h"

void disableWidget(RouteWidgets mobj);
void enableWidget(RouteWidgets mobj);
void btnNew_click (GtkWidget *widget, gpointer user_data);
gboolean entRoute_release (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void entRoute_focus (GtkWidget *widget, gpointer user_data);
void insertDataToTreeListStore(RouteWidgets *mobj);

/*
gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
void btnDemo_click (GtkWidget *widget, gpointer userdata);
void entStaName_focus (GtkWidget *widget, gpointer userdata);
void btnExit_click (GtkWidget *widget, gpointer userdata);
void btnSave_click (GtkWidget *widget, gpointer user_data);
void btnDelete_click (GtkWidget *widget, gpointer user_data);
void row_change (GtkWidget *treeView, gpointer userdata);
void update_tree_view(MyObjects *mobj, Station station, gboolean result);
void update_list_store(MyObjects *mobj, Station station, gboolean result);
*/

#endif // WIDGET_STATION_FNCT_H
