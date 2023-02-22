/*
 * station_widget_funct.c
 * purpose to store all functions about the widgets in specified module
 * name: [module]_widget_fnct.c
 */


#ifndef GTK_GTK_H
#define GTK_GTK_H
#include <gtk/gtk.h>
#endif //GTK_GTK_H
#include "functions.h"
#include "route_struct.h"
#include "station_struct.h"
#include "route_mysql_fnct.h"
#include "route_widget_fnct.h"

/*
 * to declare function name use these form:
 * 1. [widget]_[behavior] for instance, btnSave_click
 * 2. use present simple tense only
 * 3. behavior use lowercase
 * 4. Widget name use camel case lower for abbreve widget and capital for real name of widget
 * for instance btnSave_click, btn is abbreve of GtkButton and Save is name of button and 
 * click is the behavior for the button
 */

/*
void disableWidget(RouteWidgets mobj, gpointer user_data){
  RouteWidgets *mobj = (RouteWidgets*) user_data;
  gtk_widget_set_sensitive (mobj->cmbType, FALSE);
  gtk_widget_set_sensitive (mobj->entRoute, FALSE);
}

void enableWidget(RouteWidgets mobj, gpointer user_data){
  gtk_widget_set_sensitive (mobj->entRoute, TRUE);
}
*/

void btnNew_click (GtkWidget *widget, gpointer user_data){
  RouteWidgets *mobj = (RouteWidgets*) user_data;

  mobj->treeSelected = gtk_tree_view_get_selection (GTK_TREE_VIEW(mobj->treeview));
  gtk_tree_selection_unselect_all (GTK_TREE_SELECTION(mobj->treeSelected));

  gtk_entry_set_text (GTK_ENTRY(mobj->entRoute), "");
  gtk_combo_box_set_active (GTK_COMBO_BOX(mobj->cmbDirection), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX(mobj->cmbFrom), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX(mobj->cmbDest), 0);
  
  gtk_widget_set_sensitive (mobj->entRoute, TRUE);
  gtk_widget_set_sensitive (mobj->cmbDirection, FALSE);
  gtk_widget_set_sensitive (mobj->cmbFrom, FALSE);
  gtk_widget_set_sensitive (mobj->cmbDest, FALSE);
  gtk_widget_set_sensitive (mobj->btnNew, TRUE);
  gtk_widget_set_sensitive (mobj->btnSave, FALSE);
  gtk_widget_set_sensitive (mobj->btnExit, TRUE);
  gtk_widget_set_sensitive (mobj->btnDelete, FALSE);  
  mobj->edit = 0; // New, save
  
  gtk_widget_grab_focus (mobj->entRoute);
}

void entRoute_focus (GtkWidget *widget, gpointer user_data){
  change_keyb ("us");
}

gboolean entRoute_release (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
  RouteWidgets *mobj = (RouteWidgets*) user_data;
  const gchar *strRoute = gtk_entry_get_text (GTK_ENTRY(mobj->entRoute));
  if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){

    gtk_combo_box_set_active (GTK_COMBO_BOX (mobj->cmbDirection), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (mobj->cmbFrom), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (mobj->cmbDest), 0);
    gtk_widget_grab_focus (mobj->cmbDirection);
    
    return TRUE;
  }else {
    if (strlen(strRoute) > 0)
      gtk_widget_set_sensitive (mobj->cmbDirection, TRUE);
    else
      gtk_widget_set_sensitive (mobj->cmbDirection, FALSE);    
  }

  return FALSE;
}

void cmbDirection_change (GtkComboBox *combo_box, gpointer user_data) {
  RouteWidgets *mobj = (RouteWidgets*) user_data;

  // Get the active item index (i.e., the index of the currently selected item)
  gint active_item_index = gtk_combo_box_get_active (GTK_COMBO_BOX (mobj->cmbDirection));
  g_print("Selected item index: %d\n", active_item_index);

  // Do something with the active item index (e.g., print it to the console)
  mobj->directModel = gtk_combo_box_get_model (GTK_COMBO_BOX (mobj->cmbDirection));
  gtk_combo_box_get_active_iter (GTK_COMBO_BOX (mobj->cmbDirection), &mobj->directIter);
  gchar *directVal;
  gtk_tree_model_get(mobj->directModel, &mobj->directIter, 0, &directVal, -1);

  gchar *rouCode = (gchar *)gtk_entry_get_text(GTK_ENTRY(mobj->entRoute));
  Route route = {rouCode, NULL, NULL, directVal, NULL, NULL};

  route = getRouteByCode (route);
  if (route.rouNameFrom != NULL){
    g_print ("route: %s, %s, %s, direct: %s, %s, %s\n", route.rouCode,
                                                        route.rouNameFrom,
                                                        route.rouNameTo,
                                                        route.rouDirection,
                                                        route.staFrom,
                                                        route.staTo);
    GtkTreeIter from_iter, dest_iter;
    searchCombo(mobj->cmbFrom, route.staFrom, &from_iter);
    searchCombo(mobj->cmbDest, route.staTo, &dest_iter);
  
    gtk_combo_box_set_active_iter(mobj->cmbFrom, &from_iter);
    gtk_combo_box_set_active_iter(mobj->cmbDest, &dest_iter);
  } else {
    g_print ("Data not found!, %s - %s\n", route.rouCode, route.rouDirection);
    
    //gtk_combo_box_set_active_id (mobj->cmbFrom, 0);
    //gtk_combo_box_set_active_id (mobj->cmbDest, 0);
    gtk_combo_box_set_active (mobj->cmbFrom, 0);
    gtk_combo_box_set_active (mobj->cmbDest, 0);
  }
  
  gtk_widget_set_sensitive (mobj->cmbFrom, TRUE);
  gtk_widget_set_sensitive (mobj->cmbDest, TRUE);
    
  g_free (route.rouNameFrom);
  g_free (route.rouNameTo);
  g_free (route.staFrom);
  g_free (route.staTo);
  
  //g_free (rouCode); //rouCode isn't allocate, should not be freed by g_free.
  g_free (directVal);
}

void insertDataToTreeListStore(RouteWidgets *mobj) {
  // This function insert data from GList to GtkListStore
  GList *routeList = getAllRoutes ();
  for (GList *l = routeList; l != NULL; l = l->next) {
    Route *route = (Route *)l->data;
    g_print("rouCode: %s, routNameFrom: %s, rouNameTo: %s, rouDirection: %s, staFrom: %s, staTo: %s\n", route->rouCode, route->rouNameFrom, route->rouNameTo, route->rouDirection, route->staFrom, route->staTo);
    gtk_list_store_append (mobj->treeListStore, &mobj->treeIter);
    gtk_list_store_set (mobj->treeListStore, &mobj->treeIter, 0, route->rouCode,
                                                              1, route->rouNameFrom,
                                                              2, route->rouNameTo,
                                                              3, route->rouDirection,
                                                              4, route->staFrom,
                                                              5, route->staTo, -1);
  }
  g_list_free_full(routeList, freeRoute);
}

void insertDataToCmbListStore(RouteWidgets *mobj) {
  // This function insert data from GList to GtkListStore
  GtkTreeIter cmbIter;
  GList *stationList = getAllStations ();
  gtk_list_store_clear (mobj->fromListStore);
  gtk_list_store_append (mobj->fromListStore, &cmbIter);
  gtk_list_store_set (mobj->fromListStore, &cmbIter, 0, "0", 1, " ", -1);
  for (GList *l = stationList; l != NULL; l = l->next) {
    //GtkTreeIter cmbIter;
    Station *station = (Station *)l->data;
    g_print("staCode: %s, staName: %s\n", station->staCode, station->staName);
    
    gtk_list_store_append (mobj->fromListStore, &cmbIter);
    gtk_list_store_set (mobj->fromListStore, &cmbIter, 0, station->staCode,
                                                      1, station->staName, -1);
  }
  gtk_combo_box_set_active_id (GTK_COMBO_BOX (mobj->cmbFrom), 0);
  gtk_combo_box_set_active_id (GTK_COMBO_BOX (mobj->cmbDest), 0);
  g_list_free_full(stationList, freeStation);
}


/*

void btnDelete_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  
    const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
    const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
    if (staCode[0] != '\0'){
      g_print ("Delete -> Code: %s, %s\n", staCode, staName);
      gboolean result = deleteStation(staCode);
      if (result) {
        Station station = {g_strdup (staCode), g_strdup (staName)};
        GtkTreeIter *selIter = get_iter (staCode, 0, 0, mobj);
        if (selIter != NULL){
          gtk_list_store_remove (GTK_LIST_STORE (mobj->model), &mobj->iter);
        }
        g_free (station.staCode);
        g_free (station.staName);
        
        gint number_of_rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(mobj->liststore), NULL);
        if (number_of_rows == 0)
          btnNew_click (NULL, mobj);

      } else {
        g_print("Failed to delete station.\n");
      }
    }
}

void row_change (GtkWidget *treeView, gpointer userdata) {
  MyObjects *mobj = (MyObjects*) userdata;
  mobj->model = gtk_tree_view_get_model (GTK_TREE_VIEW (mobj->treeview));
  mobj->selected = gtk_tree_view_get_selection(GTK_TREE_VIEW(mobj->treeview));
  if (gtk_tree_selection_get_selected(mobj->selected, &mobj->model, &mobj->iter)){
    const gchar *staCode, *staName;
    gtk_tree_model_get (mobj->model, &mobj->iter, 0, &staCode, 1, &staName, -1);
    gtk_entry_set_text (GTK_ENTRY(mobj->entStaCode), staCode);
    
    // Get the station name from the database
    //MYSQL *conn = connect_to_db();
    Station station = {g_strdup (staCode), g_strdup (staName)};
    station = getStationNameByCode (station);
    if (station.staName != NULL) {
      gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), station.staName);
      gtk_list_store_set(mobj->liststore, &mobj->iter, 1, station.staName, -1);
      g_free(station.staName);
    } else {
      gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), "");
      gtk_list_store_remove (GTK_LIST_STORE (mobj->model), &mobj->iter);
    }
    gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
    gtk_widget_set_sensitive (mobj->entStaName, TRUE);
    gtk_button_set_label (GTK_BUTTON(mobj->btnSave), "แก้ไข");
    gtk_widget_set_sensitive (mobj->btnSave, TRUE);
    gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
    mobj->edit = 1; //edit
  }
}

void btnSave_click(GtkWidget *widget, gpointer userdata) {
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *staCode = gtk_entry_get_text(GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text(GTK_ENTRY(mobj->entStaName));
  
  if (staCode[0] != '\0' && staName[0] != '\0') {
    g_print("Save -> Code: %s, Name: %s\n", staCode, staName);

    Station station = {g_strdup(staCode), g_strdup(staName)};
    if (mobj->edit == 0) { // Insert mode.
      gboolean result = insertStation (station);
      if (result)
        update_tree_view(mobj, station, TRUE);
    } else { // Edit mode.
      gboolean result = updateStationName(station);
      if (result)
        update_list_store(mobj, station, result);
    }
    
    g_free(station.staCode);
    g_free(station.staName);

    btnNew_click(NULL, mobj);
  }
}

void update_tree_view(MyObjects *mobj, Station station, gboolean result) {
  gint number_of_rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(mobj->liststore), NULL);

  GtkTreeIter *befIter = get_iter(station.staCode, 0, -1, mobj); // ext_condition -1
  if (befIter == NULL || number_of_rows == 0) {
    gtk_list_store_append(mobj->liststore, &mobj->iter);
  } else {
    gtk_list_store_insert_before(mobj->liststore, &mobj->iter, befIter);
  }

  gtk_list_store_set(mobj->liststore, &mobj->iter, 0, station.staCode, 1, station.staName, -1); // Insert value
}

void update_list_store(MyObjects *mobj, Station station, gboolean result) {
  if (result) {
    GtkTreeIter *checkIter = get_iter(station.staCode, 0, 0, mobj); // ext_condition = 0, equal
    if (checkIter != NULL){
      GValue value = G_VALUE_INIT;
      g_value_init(&value, G_TYPE_STRING);
      g_value_set_string(&value, station.staName);
      gtk_list_store_set_value(mobj->liststore, &mobj->iter, 1, &value); // Update value
    }
  }
}

*/
