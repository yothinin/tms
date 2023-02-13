/*
 * All, these code are example and prototype of my new project 
 * in the simple code and some where have a problem or not good
 * if you (all) who found something wrong or the best way to coding
 * please tell me more to correct it.
 * 
 * yothinin@pimpanya.com
 * 
*/

#ifndef GTK_GTK_H
#define GTK_GTK_H
#include <gtk/gtk.h>
#endif //GTK_GTK_H
#include "functions.h"
#include "station_widget_fnct.h"
#include "mysql_fnct.h"
#include "station_struct.h"

void btnExit_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  g_print ("exit: %s\n", mobj->message);
  change_keyb ("us");
  gtk_widget_set_sensitive (mobj->btnExit, FALSE);
  gtk_main_quit();
}

static void activate(GtkApplication* app, gpointer userdata){
  GtkBuilder *builder;
  GtkWidget *window;

  MyObjects *mobj = (MyObjects*) userdata; // pointer to struct

  builder = gtk_builder_new_from_file("glade/tms_station.glade");
  //gtk_builder_connect_signals(builder, NULL);

  window = (GtkWidget*)gtk_builder_get_object(builder, "window");
  gtk_window_set_position (GTK_WINDOW(window), GTK_ALIGN_CENTER);
  //gtk_window_set_position (GTK_WINDOW(window), GTK_WINDOW_TOPLEVEL);
  //gtk_window_set_gravity (GTK_WINDOW(window), GDK_GRAVITY_CENTER);

  mobj->edit = 0;
  g_print ("%s\n", mobj->message);

  mobj->treeview = (GtkWidget*) gtk_builder_get_object (builder, "treeView");
  mobj->entStaCode = (GtkWidget*) gtk_builder_get_object (builder, "entStaCode");
  mobj->entStaName = (GtkWidget*) gtk_builder_get_object (builder, "entStaName");
  mobj->btnSave = (GtkWidget*) gtk_builder_get_object (builder, "btnSave");
  mobj->btnDelete = (GtkWidget*) gtk_builder_get_object (builder, "btnDelete");
  mobj->btnExit = (GtkWidget*) gtk_builder_get_object (builder, "btnExit");
  mobj->btnNew = (GtkWidget*) gtk_builder_get_object (builder, "btnNew");
  mobj->liststore = (GtkListStore*) gtk_builder_get_object (builder, "mainStore");
  mobj->btnDemo = (GtkWidget*) gtk_builder_get_object (builder, "btnDemo");
  
  MYSQL *conn = connect_to_db();
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
      //printf("%s\t", row[i] ? row[i] : "NULL");
      gtk_list_store_set (mobj->liststore, &mobj->iter, i, row[i], -1);
    }
    //printf("\n");
  }
  
  mysql_free_result(result);
  close_db_connection(conn);
  
  g_signal_connect (mobj->btnNew, "clicked", G_CALLBACK (btnNew_click), mobj); // don't use & before mobj.
  g_signal_connect (mobj->entStaCode, "focus-in-event", G_CALLBACK (entStaCode_focus), mobj);
  g_signal_connect (mobj->entStaName, "focus-in-event", G_CALLBACK (entStaName_focus), mobj);
  g_signal_connect (mobj->entStaCode, "key-release-event", G_CALLBACK (entStaCode_release), mobj);
  g_signal_connect (mobj->entStaName, "key-release-event", G_CALLBACK (entStaName_release), mobj);
  g_signal_connect (mobj->btnSave, "clicked", G_CALLBACK (btnSave_click), mobj);
  g_signal_connect (mobj->btnDelete, "clicked", G_CALLBACK (btnDelete_click), mobj);
  g_signal_connect (mobj->treeview, "cursor-changed", G_CALLBACK (row_change), mobj);
  g_signal_connect (mobj->btnExit, "clicked", G_CALLBACK (btnExit_click), mobj);
  g_signal_connect (window, "destroy", G_CALLBACK (btnExit_click), mobj);
  g_signal_connect (mobj->btnDemo, "clicked", G_CALLBACK (btnDemo_click), mobj);
  
  gtk_widget_grab_focus (mobj->btnNew);
  gtk_widget_show_all (window);
  
  g_object_unref (G_OBJECT(builder));

  gtk_main();
}

int main (int argc, char *argv[]){
	GtkApplication *app;
	int status = 0;
  
  //Initialize struct before use it.
  MyObjects mobj;
  mobj.message = "โปรแกรมข้อมูลสถานี";
    
	app = gtk_application_new("pimpanya.com", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), &mobj); // do use & before mobj
	status = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref (app);

  return status;
}
