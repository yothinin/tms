/*
 * header for station_widget_fnct.c
 */
 
#ifndef STATION_WIDGET_FNCT_H
#define STATION_WIDGET_FNCT_H
#include "station_struct.h"

gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
void btnDemo_click (GtkWidget *widget, gpointer userdata);
void entStaCode_focus (GtkWidget *widget, gpointer userdata);
void entStaName_focus (GtkWidget *widget, gpointer userdata);
void btnExit_click (GtkWidget *widget, gpointer userdata);
void btnNew_click (GtkWidget *widget, gpointer userdata);
void btnSave_click (GtkWidget *widget, gpointer user_data);
void btnDelete_click (GtkWidget *widget, gpointer user_data);
void row_change (GtkWidget *treeView, gpointer userdata);
void update_tree_view(MyObjects *mobj, Station station, gboolean result);
void update_list_store(MyObjects *mobj, Station station, gboolean result);
void insertDataToListStore(MyObjects *mobj);

#endif // STATION_WIDGET_FNCT_H
