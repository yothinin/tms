/*
 * station_struct.h
 * purpose to store a struct for the module
 * name format: [module]_struct.h
 */
#include <gtk/gtk.h>
 
#ifndef STRUCT_ROUTE_H
#define STRUCT_ROUTE_H

// MyObjects is the struct for keep widgets to send to another function
// store value in function name: activate
//
// Station is struct for store staCode and staName to passing
// to functin in mysql_fnct.c

typedef struct {
  gchar *rouCode;
  gchar *rouDirection;
  gchar *staFrom;
  gchar *staTo;
} Route;

typedef struct {
  GtkTreeModel *
} ComboBoxFrom;

typedef struct {
} ComboBoxTo;

typedef struct {
  GtkWidget *treeview ;
  GtkTreeModel *model;
  GtkListStore *store; 
  GtkTreeIter iter;
  GtkTreeSelection *selected;
  GtkWidget *entRoute; 
  GtkWidget *cmbType;
  GtkWidget *cmbFrom;
  GtkWidget *cmbDest;
  GtkWidget *btnSave;
  GtkWidget *btnDelete;
  GtkWidget *btnExit;
  gint edit;
} RouteWidgets;

#endif // STRUCT_ROUTE_H
