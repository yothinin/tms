/*
 * header for station_widget_fnct.c
 */
 
#ifndef STATION_WIDGET_FNCT_H
#define STATION_WIDGET_FNCT_H
#include "station_struct.h"

extern void btnDemo_click (GtkWidget *widget, gpointer userdata);
extern void entStaCode_focus (GtkWidget *widget, gpointer userdata);
extern void entStaName_focus (GtkWidget *widget, gpointer userdata);
extern gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
extern gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
extern void btnExit_click (GtkWidget *widget, gpointer userdata);
extern void btnNew_click (GtkWidget *widget, gpointer userdata);
extern void btnSave_click (GtkWidget *widget, gpointer user_data);
extern void btnDelete_click (GtkWidget *widget, gpointer user_data);
extern void row_change (GtkWidget *treeView, gpointer userdata);
extern void update_tree_view(MyObjects *mobj, Station station, gboolean result);
extern void update_list_store(MyObjects *mobj, Station station, gboolean result);
extern void insertDataToListStore(MyObjects *mobj);
#endif // STATION_WIDGET_H
