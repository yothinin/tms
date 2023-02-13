/*
 * header for station_widget_fnct.c
 */
 
#ifndef STATION_WIDGET_FNCT_H
#define STATION_WIDGET_FNCT_H
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
#endif // STATION_WIDGET_H
