/*
 * header for station_widget_fnct.c
 */
 
#ifndef WIDGET_ROUTE_FNCT_H
#define WIDGET_ROUTE_FNCT_H
#include "route_struct.h"
#include "route_mysql_fnct.h"

void disableWidget(RouteWidgets mobj);
void enableWidget(RouteWidgets mobj);
void btnNew_click (GtkWidget *widget, gpointer user_data);
gboolean entRoute_release (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void entRoute_focus (GtkWidget *widget, gpointer user_data);
void insertDataToTreeListStore (RouteWidgets *mobj);
void insertDataToCmbListStore (RouteWidgets *mobj);
void cmbDirection_change (GtkComboBox *combo_box, gpointer user_data);
void set_buttons_sensitive(GtkComboBox *cmb_from, GtkComboBox *cmb_dest, GtkButton *btn_save, GtkButton *btn_delete, gint first_item_index);
gboolean validateRouteInput(RouteWidgets *routeWidgets);
void btnSave_click(GtkButton *button, gpointer user_data);
void clearRouteInput(RouteWidgets *routeWidgets);
void cmbFrom_change(GtkComboBox *cmbFrom, gpointer user_data);
void cmbDest_change(GtkComboBox *cmbDest, gpointer user_data);
void row_change(GtkTreeSelection *selection, gpointer user_data);
gint find_combo_box_index(GtkComboBox *combo_box, const gchar *id);
void enableWidgets(RouteWidgets *mobj, gboolean enable);
void btnDelete_click (GtkWidget *widget, gpointer userdata);
gboolean cmbDirection_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean cmbFrom_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean cmbDest_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

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
