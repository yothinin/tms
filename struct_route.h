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

enum {
  COL_ROUTE = 0,
  COL_FROM,
  COL_TO,
  COL_FROMCODE,
  COL_DESTCODE,
  COL_TYPE,
  NUM_COLS
};

typedef struct {
  gchar *rouCode;
  gchar *rouDirection;
  gchar *staFrom;
  gchar *staTo;
} Route;

typedef struct {
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *treeview ;
  GtkTreeModel *model;
  GtkListStore *treeListStore; 
  GtkTreeIter treeIter;
  GtkTreeSelection *treeSelected;
  GtkWidget *entRoute; 
  GtkWidget *btnNew;
  GtkWidget *btnSave;
  GtkWidget *btnDelete;
  GtkWidget *btnExit;
  gint edit;

  GtkWidget *cmbType;
  GtkTreeModel *typeModel;
  GtkListStore *typeListStore;
  GtkTreeIter *typeIter;

  GtkWidget *cmbFrom;
  GtkTreeModel *fromModel;
  GtkListStore *fromListStore;
  GtkTreeIter *fromIter;

  GtkWidget *cmbDest;
  GtkTreeModel *destModel;
  GtkListStore *destListStore;
  GtkTreeIter *destIter;
  
  gchar *message;
  
} RouteWidgets;

#endif // STRUCT_ROUTE_H
