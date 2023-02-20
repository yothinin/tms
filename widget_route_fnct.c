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
#include "struct_route.h"
#include "widget_route_fnct.h"
//#include "mysql_route_fnct.h"

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

  //mobj->treeSelected = gtk_tree_view_get_selection (GTK_TREE_VIEW(mobj->treeview));
  //gtk_tree_selection_unselect_all (GTK_TREE_SELECTION(mobj->treeSelected));

  gtk_widget_set_sensitive (mobj->entRoute, TRUE);
  gtk_widget_set_sensitive (mobj->cmbType, FALSE);
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

    const gchar *const_rouCode = gtk_entry_get_text(GTK_ENTRY(mobj->entRoute));
    gchar *rouCode = g_strdup(const_rouCode);
    Route route = {rouCode, NULL};

    //station = getStationNameByCode (station);
    //gtk_entry_set_text (GTK_ENTRY (mobj->entStaName), station.staName == NULL?"":station.staName);

    //if (station.staName != NULL){
      //gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
      //mobj->edit=1; // UPDATE
      //gtk_button_set_label (GTK_BUTTON (mobj->btnSave), "แก้ไข");
      //gtk_widget_set_sensitive (mobj->btnSave, TRUE);
      //gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
    //} // CHECK LATER FOR NEED TO CREATE ELSE BLOCK FOR mobj->edit = 0;
    
    gtk_widget_grab_focus (mobj->cmbType);
    
    g_free (rouCode);
    //g_free (route.staName);

    return TRUE;
  }else {
    if (strlen(strRoute) > 0)
      gtk_widget_set_sensitive (mobj->cmbType, TRUE);
    else
      gtk_widget_set_sensitive (mobj->cmbType, FALSE);    
  }

  return FALSE;
}


/*
void btnDemo_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  g_print ("demo clicked\n");
  
  int i;
  for (i = 0; i < 20000; i++){
    gtk_list_store_append (mobj->liststore, &mobj->iter);
    gchar code[6], name[6];
    sprintf (code, "%05d", i);
    sprintf (name, "%05d", i);
    gtk_list_store_set (mobj->liststore, &mobj->iter, 0, code, 1, name, -1); // Insert value
  }
}

void entStaName_focus (GtkWidget *widget, gpointer userdata){
  change_keyb ("th");
}

gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *staname = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){

    gtk_widget_grab_focus (mobj->btnSave);

    return TRUE;
  }else {
    if (strlen(staname) > 0)
      gtk_widget_set_sensitive (mobj->btnSave, TRUE);
    else
      gtk_widget_set_sensitive (mobj->btnSave, FALSE);    
  }

  return FALSE;
}

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

//void row_change (GtkWidget *treeView, gpointer userdata) {
  //MyObjects *mobj = (MyObjects*) userdata;
  //mobj->model = gtk_tree_view_get_model (GTK_TREE_VIEW (mobj->treeview));
  //mobj->selected = gtk_tree_view_get_selection(GTK_TREE_VIEW(mobj->treeview));
  //if (gtk_tree_selection_get_selected(mobj->selected, &mobj->model, &mobj->iter)){
    //const gchar *staCode, *staName;
    //gtk_tree_model_get (mobj->model, &mobj->iter, 0, &staCode, 1, &staName, -1);
    //gtk_entry_set_text (GTK_ENTRY(mobj->entStaCode), staCode);
    //gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), staName);
    //gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
    //gtk_widget_set_sensitive (mobj->entStaName, TRUE);
    //gtk_button_set_label (GTK_BUTTON(mobj->btnSave), "แก้ไข");
    //gtk_widget_set_sensitive (mobj->btnSave, TRUE);
    //gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
    //mobj->edit = 1; //edit
  //}
//}

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

void insertDataToListStore(MyObjects *mobj) {
  MYSQL *conn;
  conn = connect_to_db();
  if (conn == NULL) {
    fprintf(stderr, "Error: failed to connect to database\n");
    exit (1);
  }
  
  const char *sql = "SELECT sta_code, sta_name FROM station ORDER BY sta_code";
  if (query(conn, sql)) {
    fprintf(stderr, "Error: failed to execute query\n");
    close_db_connection(conn);
    exit (1);
  }
  
  MYSQL_RES *result = mysql_store_result(conn);
  if (result == NULL) {
    fprintf(stderr, "Error: failed to get result\n");
    close_db_connection(conn);
    exit (1);
  }
  
  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) {
    gtk_list_store_append (mobj->liststore, &mobj->iter);
    for (int i = 0; i < num_fields; i++) {
      gtk_list_store_set (mobj->liststore, &mobj->iter, i, row[i], -1);
    }
  }
  
  mysql_free_result(result);
  close_db_connection(conn);
}

*/
