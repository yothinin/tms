/*
 * functions.c
 * purpose for store functions to share all module
 */

#ifndef GTK_GTK_H
#define GTK_GTK_H
#include <gtk/gtk.h>
#endif //GTK_GTK_H
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include "struct_station.h"

void change_keyb (gchar *new_group){
  Display *dpy = XOpenDisplay(NULL);
  XkbRF_VarDefsRec vd;
  XkbRF_GetNamesProp(dpy, NULL, &vd);

  gint i = 0;
  const gchar *tok = strtok(vd.layout, ",");
  while (tok != NULL) {
    if (g_strcmp0 (tok, new_group) == 0)
      break;
    i++;
    tok = strtok(NULL, ",");
  }

  XkbLockGroup(dpy, XkbUseCoreKbd, i); // change group
  printf ("Changed keyboard to: %s\n", new_group);

  XCloseDisplay(dpy);
}

// return pointer to GtkTreeIter, use *
// ex_condition, we stop looping when result is -1 = before, 0 = equal, 1 = after
GtkTreeIter *get_iter (const gchar* str, gint col, int ext_condition, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  gint number_of_rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(mobj->liststore), NULL);
  mobj->model = gtk_tree_view_get_model (GTK_TREE_VIEW (mobj->treeview));
  if (gtk_tree_model_get_iter_first (mobj->model, &mobj->iter)){
    gchar *staCode;
    gint count=1;
    do {
      gtk_tree_model_get (mobj->model, &mobj->iter, col, &staCode, -1);

      // sta after staCode, exit and insert before staCode.
      if (ext_condition == -1 && g_utf8_collate (str, staCode) < 0) break;
      // str equal staCode, exit and update this staCode.
      if (ext_condition == 0 && g_utf8_collate (str, staCode) == 0) break;
      // str before staCode, exit we don't use it here.
      if (ext_condition == 1 && g_utf8_collate (str, staCode) > 0) break;

      count++;
      g_free (staCode); // addnew
    } while (gtk_tree_model_iter_next (mobj->model, &mobj->iter));

    if (count > number_of_rows){
      g_print ("EOF, data not found (ALL=%d)\n", number_of_rows);
      return NULL;
    }else{
      g_print ("found at: %d of %d\n", count, number_of_rows);
    }
    //g_free (staCode); //move to do block
  }
  
  return (&mobj->iter); // must use & before iter
}

void display_warning_message(const gchar *message) {
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "%s", message);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

