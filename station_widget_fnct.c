/*
 * station_widget_funct.c
 * purpose to store all functions about the widgets in specified module
 * name: [module]_widget_fnct.c
 */


#ifndef GTK_GTK_H
#define GTK_GTK_H
#include <gtk/gtk.h>
#endif //GTK_GTK_H
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include "functions.h"
#include "station_struct.h"


/*
 * to declare function name use these form:
 * 1. [widget]_[behavior] for instance, btnSave_click
 * 2. use present simple tense only
 * 3. behavior use lowercase
 * 4. Widget name use camel case lower for abbreve widget and capital for real name of widget
 * for instance btnSave_click, btn is abbreve of GtkButton and Save is name of button and 
 * click is the behavior for the button
 */

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
  
void entStaCode_focus (GtkWidget *widget, gpointer userdata){
  change_keyb ("us");
}

gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *stacode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){

    const gchar *staCode = gtk_entry_get_text (GTK_ENTRY (mobj->entStaCode));
    GtkTreeIter *checkIter = get_iter(staCode, 0, 0, mobj); // ext_condition = 0, equal
                                                           // use equal because search to find the code.
    if (gtk_list_store_iter_is_valid (mobj->liststore, checkIter)){
      const gchar *staName;
      gtk_tree_model_get (GTK_TREE_MODEL (mobj->model), &mobj->iter, 1, &staName, -1);
      gtk_entry_set_text (GTK_ENTRY (mobj->entStaName), staName);
      gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
      mobj->edit=1;
      gtk_button_set_label (GTK_BUTTON (mobj->btnSave), "แก้ไข");
      gtk_widget_set_sensitive (mobj->btnSave, TRUE);
      gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
    }
    gtk_widget_grab_focus (mobj->entStaName);

    return TRUE;
  }else {
    if (strlen(stacode) > 0)
      gtk_widget_set_sensitive (mobj->entStaName, TRUE);
    else
      gtk_widget_set_sensitive (mobj->entStaName, FALSE);    
  }

  return FALSE;
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

void btnNew_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;

  GtkTreeSelection *selected = gtk_tree_view_get_selection (GTK_TREE_VIEW(mobj->treeview));
  gtk_tree_selection_unselect_all (GTK_TREE_SELECTION(selected));

  gtk_widget_set_sensitive (mobj->entStaCode, TRUE);
  gtk_widget_set_sensitive (mobj->entStaName, FALSE);
  gtk_entry_set_text (GTK_ENTRY(mobj->entStaCode), "");
  gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), "");
  gtk_button_set_label (GTK_BUTTON(mobj->btnSave), "บันทึก");
  gtk_widget_set_sensitive (mobj->btnSave, FALSE);
  gtk_widget_set_sensitive (mobj->btnDelete, FALSE);
  gtk_widget_grab_focus (mobj->entStaCode);
  mobj->edit = 0; // New, save
}

void btnSave_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (staCode[0] != '\0' && staName[0] != '\0'){
    g_print ("Save -> Code: %s, Name: %s\n", staCode, staName);
    if (mobj->edit == 0){ // Insert mode.
      GtkTreeIter *befIter = get_iter(staCode, 0, -1, mobj); // ext_condition -1
      if (gtk_list_store_iter_is_valid (mobj->liststore, befIter)){
        gtk_list_store_insert_before (mobj->liststore, &mobj->iter, befIter);
      }else{
        gtk_list_store_append (mobj->liststore, &mobj->iter);
      }
      gtk_list_store_set (mobj->liststore, &mobj->iter, 0, staCode, 1, staName, -1); // Insert value
    }else{ // Edit mode.
      GValue value = G_VALUE_INIT;
      g_value_init(&value, G_TYPE_STRING);
      g_value_set_string (&value, staName);
      gtk_list_store_set_value (mobj->liststore, &mobj->iter, 1, &value); // Update value
      
      // ---------- check GValue --------------//
      if (G_VALUE_HOLDS_STRING(&value)) {
        const gchar *string_value = g_value_get_string(&value);
        g_print("Value is a string: %s\n", string_value);
      }
    
    }
    btnNew_click(NULL, mobj);
  } // if staCode and Name are empty, we do nothing.
}

void btnDelete_click (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (staCode[0] != '\0'){
    g_print ("Delete -> Code: %s, %s\n", staCode, staName);
    mobj->model = gtk_tree_view_get_model(GTK_TREE_VIEW(mobj->treeview));
    mobj->selected = gtk_tree_view_get_selection(GTK_TREE_VIEW(mobj->treeview));
    if (gtk_tree_selection_get_selected(mobj->selected, &mobj->model, &mobj->iter)){
      gtk_list_store_remove (GTK_LIST_STORE(mobj->model), &mobj->iter);
      gint number_of_rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(mobj->liststore), NULL);
      if (number_of_rows == 0){
        btnNew_click (NULL, mobj);
      }
    }else{
      g_print ("Treeview doesn't select.\n");
      GtkTreeIter *checkIter = get_iter(staCode, 0, 0, mobj); // ext_condition = 0, search for equal
      if (gtk_list_store_iter_is_valid (mobj->liststore, checkIter)){
        gtk_list_store_remove (mobj->liststore, &mobj->iter);
        btnNew_click (NULL, mobj);
      }
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
    gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), staName);
    gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
    gtk_widget_set_sensitive (mobj->entStaName, TRUE);
    gtk_button_set_label (GTK_BUTTON(mobj->btnSave), "แก้ไข");
    gtk_widget_set_sensitive (mobj->btnSave, TRUE);
    gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
    mobj->edit = 1; //edit
  }
}
