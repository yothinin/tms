#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gprintf.h>
#include "struct_route.h"
#include "widget_route_fnct.h"

gboolean on_main_window_delete_event(GtkWidget *widget, GdkEvent *event, gpointer userdata) {
  RouteWidgets *mobj = (RouteWidgets*) userdata;
  GtkWidget *dialog;
  gint result;

  dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(mobj->window),
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_QUESTION,
                                              GTK_BUTTONS_NONE,
                                              "<span size='large' weight='bold'>Are you sure you want to exit?</span>");

  gtk_dialog_add_buttons(GTK_DIALOG(dialog),
                         "Yes",
                         GTK_RESPONSE_YES,
                         "No",
                         GTK_RESPONSE_NO,
                         NULL);

  result = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);

  if (result == GTK_RESPONSE_YES) {
    g_print("Main window close button clicked\nExit: %s\n", mobj->message);
    gtk_main_quit();
    return FALSE;
  } else {
    return TRUE;
  }
}

void btnExit_click(GtkWidget *widget, gpointer userdata) {
  RouteWidgets *mobj = (RouteWidgets*) userdata;
  GtkWidget *dialog;
  gint result;

  dialog = gtk_message_dialog_new(GTK_WINDOW(mobj->window),
                                  GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_QUESTION,
                                  GTK_BUTTONS_YES_NO,
                                  "Are you sure you want to exit?");

  result = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);

  if (result == GTK_RESPONSE_YES) {
    g_print("btnExit.Clicked\nExit: %s\n", mobj->message);
    gtk_main_quit();
  }
  // If the user clicked "No" or closed the dialog box, do nothing and return to the program.
}

/*
static GtkTreeModel *
create_and_fill_model (void) {

  GtkListStore *store = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

  //Append a row and file in some data
  GtkTreeIter iter;
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      COL_ROUTE, "18",
                      COL_FROM, "กรุงเทพฯ",
                      COL_TO, "เขียงใหม่",
                      COL_FROMCODE, "10000",
                      COL_DESTCODE, "50000",
                      COL_TYPE, "O",
                      -1);

  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      COL_ROUTE, "20",
                      COL_FROM, "กรุงเทพฯ",
                      COL_TO, "ขอนแก่น",
                      COL_FROMCODE, "10000",
                      COL_DESTCODE, "40000",
                      COL_TYPE, "O",
                      -1);
                      
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      COL_ROUTE, "31",
                      COL_FROM, "กรุงเทพฯ",
                      COL_TO, "สุรินทร์",
                      COL_FROMCODE, "10000",
                      COL_DESTCODE, "34000",
                      COL_TYPE, "O",
                      -1);

  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      0, "31",
                      1, "สุรินทร์",
                      2, "กรุงเทพฯ",
                      3, "34000",
                      4, "10000",
                      5, "I",
                      -1);

  return GTK_TREE_MODEL (store);
}

G_MODULE_EXPORT
void on_btnNew_clicked (GtkWidget *widget, gpointer userdata){
  g_print ("btnNew::clicked\n");

  GtkWidget *treeView = (GtkWidget*) gtk_builder_get_object (builder, "treeviewRoute");
  GtkWidget *entRoute = (GtkWidget*) gtk_builder_get_object (builder, "entRoute");
  GtkWidget *cmbType = (GtkWidget*) gtk_builder_get_object (builder, "cmbType");
  GtkWidget *cmbFrom = (GtkWidget*) gtk_builder_get_object (builder, "cmbFrom");
  GtkWidget *cmbDest = (GtkWidget*) gtk_builder_get_object (builder, "cmbDest");
  GtkWidget *btnSave = (GtkWidget*) gtk_builder_get_object (builder, "btnSave");
  GtkWidget *btnDelete = (GtkWidget*) gtk_builder_get_object (builder, "btnDelete");
  
  GtkTreeSelection *selected = gtk_tree_view_get_selection (GTK_TREE_VIEW(treeView));
  gtk_tree_selection_unselect_all (GTK_TREE_SELECTION(selected));

  gtk_entry_set_text (GTK_ENTRY(entRoute), "");
  gtk_combo_box_set_active (GTK_COMBO_BOX(cmbType), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX(cmbFrom), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX(cmbDest), 0);
  gtk_widget_set_sensitive (entRoute, TRUE);
  gtk_widget_set_sensitive (cmbType, TRUE);
  gtk_widget_set_sensitive (btnSave, FALSE);
  gtk_widget_set_sensitive (btnDelete, FALSE);

  gtk_widget_grab_focus (entRoute);
}

static GtkTreeModel *
create_model_from (void) {

  GtkListStore *store = GTK_LIST_STORE(gtk_builder_get_object(builder, "stationLists"));
  GtkTreeIter iter;


  //int i;
  //store = GTK_LIST_STORE(gtk_builder_get_object(builder, "listForm"));
  
  //for (i = 0; i < G_N_ELEMENTS(std); ++i){
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "00000", 1, "", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "10000", 1, "กรุงเทพฯ", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "10010", 1, "วิภาวดี", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "34000", 1, "สุรินทร์", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "40000", 1, "ขอนแก่น", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "50000", 1, "เชียงใหม่", -1);
  //}

  return (GTK_TREE_MODEL(store));
}


G_MODULE_EXPORT
void btnSave_clicked_cb (GtkWidget *widget, gpointer userdata){
  g_print ("btnSave::Clicked\n");
}

G_MODULE_EXPORT
void btnDelete_clicked_cb (GtkWidget *widget, gpointer userdata){
  g_print ("btnCancel::Clicked\n");
}

GtkTreeIter cmbSearch (GtkWidget *combo, const gchar *text_to_search){
  GtkTreeModel *model;
  GtkTreeIter iter;
  gint row = 0;

  model = gtk_combo_box_get_model (GTK_COMBO_BOX(combo));

  if (gtk_tree_model_get_iter_first(model, &iter)) {
    do {
      gchar *value;
      gtk_tree_model_get(model, &iter, 0, &value, -1);

      if (g_strcmp0(value, text_to_search) == 0) {
        g_print("Text found at row %d\n", row);
        break;
      }

      g_free(value);
      row++;
    } while (gtk_tree_model_iter_next(model, &iter));
  }

  return (iter);
}

G_MODULE_EXPORT
void rowChanged (GtkWidget *treeView, gpointer userdata) {
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));
  GtkTreeIter iter;

  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));
  if (gtk_tree_selection_get_selected(selection, &model, &iter)){
    const gchar *route, *from, *dest, *fromCode, *destCode, *rouType;
    gtk_tree_model_get 
        (model, &iter, 0, &route, 1, &from, 2, &dest, 3, &fromCode, 4, &destCode, 5, &rouType, -1);

    disableWidget();

    GtkEntry *entRoute = GTK_ENTRY((GtkWidget*) gtk_builder_get_object(builder, "entRoute"));    
    gtk_entry_set_text (entRoute, route);
    GtkWidget *cmbFrom = (GtkWidget*) gtk_builder_get_object (builder, "cmbFrom");
    GtkWidget *cmbDest = (GtkWidget*) gtk_builder_get_object (builder, "cmbDest");
    GtkWidget *cmbType = (GtkWidget*) gtk_builder_get_object (builder, "cmbType");
    GtkWidget *btnSave = (GtkWidget*) gtk_builder_get_object (builder, "btnSave");
    GtkWidget *btnDelete = (GtkWidget*) gtk_builder_get_object (builder, "btnDelete");
    GtkListStore *store;

    gtk_widget_set_sensitive (btnSave, TRUE);
    gtk_widget_set_sensitive (btnDelete, TRUE);

    iter = cmbSearch (cmbFrom, fromCode);
    model = gtk_combo_box_get_model (GTK_COMBO_BOX(cmbFrom));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (GTK_COMBO_BOX(cmbFrom)));
    if (gtk_list_store_iter_is_valid (store, &iter))
      gtk_combo_box_set_active_iter (GTK_COMBO_BOX(cmbFrom), &iter);
    else
      gtk_combo_box_set_active (GTK_COMBO_BOX(cmbFrom), 0);

    iter = cmbSearch (cmbDest, destCode);    
    model = gtk_combo_box_get_model (GTK_COMBO_BOX(cmbDest));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (GTK_COMBO_BOX(cmbDest)));

    if (gtk_list_store_iter_is_valid (store, &iter))
      gtk_combo_box_set_active_iter (GTK_COMBO_BOX(cmbDest), &iter);
    else
      gtk_combo_box_set_active (GTK_COMBO_BOX(cmbDest), 0);

    iter = cmbSearch (cmbType, rouType);
    model = gtk_combo_box_get_model (GTK_COMBO_BOX(cmbType));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (GTK_COMBO_BOX(cmbType)));

    if (gtk_list_store_iter_is_valid (store, &iter))
      gtk_combo_box_set_active_iter (GTK_COMBO_BOX(cmbType), &iter);
    else
      gtk_combo_box_set_active (GTK_COMBO_BOX(cmbType), 0);

  }else{
    g_print ("no row selected.\n");
  }
}

G_MODULE_EXPORT
void fromChanged (GtkWidget *widget, gpointer userdata){
  GtkTreeModel *model;
  GtkTreeIter iter;

  gchar *stationCode;
  gchar *stationFrom;

  model = gtk_combo_box_get_model (GTK_COMBO_BOX(widget));
  gtk_combo_box_get_active_iter (GTK_COMBO_BOX(widget), &iter);
  gtk_tree_model_get(model, &iter, 0, &stationCode, 1, &stationFrom, -1);

  g_print ("ต้นทาง: %s - %s\n", stationCode, stationFrom);

  g_free (stationCode);
  g_free (stationFrom);
}

G_MODULE_EXPORT
void destChanged (GtkWidget *widget, gpointer userdata){
  GtkTreeModel *model;
  GtkTreeIter iter;

  gchar *stationCode;
  gchar *stationFrom;

  model = gtk_combo_box_get_model (GTK_COMBO_BOX(widget));
  gtk_combo_box_get_active_iter (GTK_COMBO_BOX(widget), &iter);
  gtk_tree_model_get(model, &iter, 0, &stationCode, 1, &stationFrom, -1);

  g_print ("ปลายทาง: %s - %s\n", stationCode, stationFrom);

  g_free (stationCode);
  g_free (stationFrom);
}
*/

static void activate(GtkApplication* app, gpointer userdata){
  RouteWidgets *mobj = (RouteWidgets*) userdata; // pointer to struct

  mobj->builder = gtk_builder_new_from_file("glade/tms_route.glade");
  
  mobj->window = (GtkWidget*)gtk_builder_get_object(mobj->builder, "window");
  gtk_window_set_position (GTK_WINDOW(mobj->window), GTK_ALIGN_CENTER);
  
  mobj->edit = 0;
  g_print ("%s\n", mobj->message);

  mobj->treeview = (GtkWidget*) gtk_builder_get_object (mobj->builder, "treeViewRoute");
  mobj->entRoute = (GtkWidget*) gtk_builder_get_object (mobj->builder, "entRoute");
  mobj->cmbType = (GtkWidget*) gtk_builder_get_object (mobj->builder, "cmbType");
  mobj->cmbFrom = (GtkWidget*) gtk_builder_get_object (mobj->builder, "cmbFrom");
  mobj->cmbDest = (GtkWidget*) gtk_builder_get_object (mobj->builder, "cmbDest");
  mobj->btnNew = (GtkWidget*) gtk_builder_get_object (mobj->builder, "btnNew");
  mobj->btnSave = (GtkWidget*) gtk_builder_get_object (mobj->builder, "btnSave");
  mobj->btnExit = (GtkWidget*) gtk_builder_get_object (mobj->builder, "btnExit");
  mobj->btnDelete = (GtkWidget*) gtk_builder_get_object (mobj->builder, "btnDelete");
  mobj->treeListStore = (GtkListStore*) gtk_builder_get_object (mobj->builder, "liststore1");
  mobj->typeListStore = (GtkListStore*) gtk_builder_get_object (mobj->builder, "routeDirection");
  mobj->fromListStore = (GtkListStore*) gtk_builder_get_object (mobj->builder, "stationLists");
  mobj->destListStore = (GtkListStore*) gtk_builder_get_object (mobj->builder, "stationLists");
  
  insertDataToTreeListStore (mobj);

  /*
  g_signal_connect (mobj->entStaName, "focus-in-event", G_CALLBACK (entStaName_focus), mobj);
  g_signal_connect (mobj->entStaName, "key-release-event", G_CALLBACK (entStaName_release), mobj);
  g_signal_connect (mobj->btnSave, "clicked", G_CALLBACK (btnSave_click), mobj);
  g_signal_connect (mobj->btnDelete, "clicked", G_CALLBACK (btnDelete_click), mobj);
  g_signal_connect (mobj->treeview, "cursor-changed", G_CALLBACK (row_change), mobj);
  g_signal_connect (mobj->btnDemo, "clicked", G_CALLBACK (btnDemo_click), mobj);
  */

  g_signal_connect (mobj->entRoute, "focus-in-event", G_CALLBACK (entRoute_focus), mobj);
  g_signal_connect (mobj->entRoute, "key-release-event", G_CALLBACK (entRoute_release), mobj);
  g_signal_connect (mobj->btnNew, "clicked", G_CALLBACK (btnNew_click), mobj);
  g_signal_connect (mobj->btnExit, "clicked", G_CALLBACK (btnExit_click), mobj);
  //g_signal_connect (mobj->window, "destroy", G_CALLBACK (btnExit_click), mobj);
  g_signal_connect(mobj->window, "delete-event", G_CALLBACK(on_main_window_delete_event), mobj);

  /*
  gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
  gtk_widget_set_sensitive (mobj->entStaName, FALSE);
  gtk_widget_set_sensitive (mobj->btnSave, FALSE);
  gtk_widget_set_sensitive (mobj->btnDelete, FALSE);
  */
  
  gtk_widget_grab_focus (mobj->btnNew);
  gtk_widget_show_all (mobj->window);
  
  g_object_unref (G_OBJECT(mobj->builder));

  gtk_main();
}

int main (int argc, char *argv[]){
	GtkApplication *app;
	int status = 0;
  
  //Initialize struct before use it.
  RouteWidgets mobj;
  mobj.message = "โปรแกรมข้อมูลเส้นทาง";
    
	app = gtk_application_new("pimpanya.com", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), &mobj); // do use & before mobj
	status = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref (app);

  return status;
}

//int main(int argc, char *argv[]){

  //gtk_init(&argc, &argv);

  //builder = gtk_builder_new_from_file("glade/tms_route.glade");
  //gtk_builder_connect_signals(builder, NULL);

  //window = (GtkWidget*)gtk_builder_get_object(builder, "window");
  //gtk_window_set_position (GTK_WINDOW(window), GTK_WINDOW_TOPLEVEL);
  //gtk_window_set_gravity (GTK_WINDOW(window), GDK_GRAVITY_CENTER);

  //GtkWidget *view = (GtkWidget*)gtk_builder_get_object(builder, "treeviewRoute");
  //GtkTreeModel *model = create_and_fill_model ();

  //gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  //GtkWidget *cmbFrom = (GtkWidget*) gtk_builder_get_object (builder, "cmbFrom");
  //model = create_model_from();
  //gtk_combo_box_set_model (GTK_COMBO_BOX (cmbFrom), model);

  //gtk_widget_show_all(GTK_WIDGET(window));

  //gtk_main();

  //return 0;
//}
