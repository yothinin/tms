/*
 * All, these code are example and prototype of my new project 
 * in the simple code and some where have a problem or not good
 * if you (all) who found something wrong or the best way to coding
 * please tell me more to correct it.
 * 
 * yothinin@pimpanya.com
 * 
*/

#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>


// The struct for keep widgets to send to another function
// store value in function name: activate
typedef struct _MyObjects{
  GtkWidget *treeview;
  GtkTreeModel *model;
  GtkListStore *liststore; 
  GtkTreeIter iter;
  GtkTreeSelection *selected;
	GtkWidget *entStaCode; 
	GtkWidget *entStaName;
	GtkWidget *btnSave;
  GtkWidget *btnDelete;
  GtkWidget *btnExit;
  GtkWidget *btnNew;
  gint edit;
  gchar *message;
}MyObjects;

//---------------------------------------------------------------//
GtkTreeIter *getIter (const gchar* str, gint col, int direction, gpointer userdata);
void changeKey (gchar *new_group);
void on_entStaCode_focus (GtkWidget *widget, gpointer userdata);
static gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
static gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata);
static void btnExit_clicked (GtkWidget *widget, gpointer userdata);
static void btnNewClicked (GtkWidget *widget, gpointer userdata);
static void btnSave_clicked (GtkWidget *widget, gpointer user_data);
static void btnDelete_clicked (GtkWidget *widget, gpointer user_data);
void rowChanged (GtkWidget *treeView, gpointer userdata);
static void activate(GtkApplication* app, gpointer user_data);
//--------------------------------------------------------------//

void changeKey (gchar *new_group){
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

void on_entStaCode_focus (GtkWidget *widget, gpointer userdata){
  changeKey ("us");
  //g_print ("entStaCode: focus\n");
}

static gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *stacode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){

    const gchar *staCode = gtk_entry_get_text (GTK_ENTRY (mobj->entStaCode));
    GtkTreeIter *checkIter = getIter(staCode, 0, 0, mobj); // direction = 0, equal

    if (gtk_list_store_iter_is_valid (mobj->liststore, checkIter)){
      const gchar *staName;
      gtk_tree_model_get (GTK_TREE_MODEL (mobj->model), &mobj->iter, 1, &staName, -1);
      gtk_entry_set_text (GTK_ENTRY (mobj->entStaName), staName);
      gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
      mobj->edit=1;
      gtk_button_set_label (GTK_BUTTON (mobj->btnSave), "แก้ไข");
      gtk_widget_set_sensitive (mobj->btnSave, TRUE);
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

void on_entStaName_focus (GtkWidget *widget, gpointer userdata){
  changeKey ("th");
  //g_print ("entStaName: focus\n");
}

static gboolean entStaName_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
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

static void btnExit_clicked (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  g_print ("exit: %s\n", mobj->message);
  changeKey ("us");
  gtk_main_quit();
}

static void btnNewClicked (GtkWidget *widget, gpointer userdata){
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

// return pointer to GtkTreeIter, use *
// direction, -1 = before, 0 = equal, 1 = after
GtkTreeIter *getIter (const gchar* str, gint col, int direction, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  //gint number_of_rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(mobj->liststore), NULL);
  mobj->model = gtk_tree_view_get_model (GTK_TREE_VIEW (mobj->treeview));
  if (gtk_tree_model_get_iter_first (mobj->model, &mobj->iter)){
    gchar *staCode;
    do {
      gtk_tree_model_get (mobj->model, &mobj->iter, col, &staCode, -1);
      if (direction == -1)
        if (g_utf8_collate (str, staCode) < 0) 
          break;
      if (direction == 0)
        if (g_utf8_collate (str, staCode) == 0)
          break;
      if (direction == 1)
        if (g_utf8_collate (str, staCode) > 0)
          break;
    } while (gtk_tree_model_iter_next (mobj->model, &mobj->iter));

    g_free (staCode);
  }
  
  return (&mobj->iter); // must use & before iter
}

static void btnSave_clicked (GtkWidget *widget, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (staCode[0] != '\0' && staName[0] != '\0'){
    g_print ("Save -> Code: %s, Name: %s\n", staCode, staName);
    if (mobj->edit == 0){      
      GtkTreeIter *befIter = getIter(staCode, 0, -1, mobj); // direction -1
      if (gtk_list_store_iter_is_valid (mobj->liststore, befIter)){
        gtk_list_store_insert_before (mobj->liststore, &mobj->iter, befIter);
      }else{
        gtk_list_store_append (mobj->liststore, &mobj->iter);
      }
      gtk_list_store_set (mobj->liststore, &mobj->iter, 0, staCode, 1, staName, -1); // Insert value
    }else{
      GValue value = G_VALUE_INIT;
      g_value_init(&value, G_TYPE_STRING);
      g_value_set_string (&value, staName);
      gtk_list_store_set_value (mobj->liststore, &mobj->iter, 1, &value); // Update value
    }
    btnNewClicked(NULL, mobj);
  }
}

static void btnDelete_clicked (GtkWidget *widget, gpointer userdata){
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
        //newform(mobj);
        btnNewClicked (NULL, mobj);
      }
    }
  }
}

void rowChanged (GtkWidget *treeView, gpointer userdata) {
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

  mobj->message = "เริ่มต้นโปรแกรม";
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
  
  g_signal_connect (mobj->btnNew, "clicked", G_CALLBACK (btnNewClicked), mobj); // don't use & before mobj.
  g_signal_connect (mobj->entStaCode, "focus-in-event", G_CALLBACK (on_entStaCode_focus), mobj);
  g_signal_connect (mobj->entStaName, "focus-in-event", G_CALLBACK (on_entStaName_focus), mobj);
  g_signal_connect (mobj->entStaCode, "key-release-event", G_CALLBACK (entStaCode_release), mobj);
  g_signal_connect (mobj->entStaName, "key-release-event", G_CALLBACK (entStaName_release), mobj);
  g_signal_connect (mobj->btnSave, "clicked", G_CALLBACK (btnSave_clicked), mobj);
  g_signal_connect (mobj->btnDelete, "clicked", G_CALLBACK (btnDelete_clicked), mobj);
  g_signal_connect (mobj->treeview, "cursor-changed", G_CALLBACK (rowChanged), mobj);
  g_signal_connect (mobj->btnExit, "clicked", G_CALLBACK (btnExit_clicked), mobj);
  g_signal_connect (window, "destroy", G_CALLBACK (btnExit_clicked), mobj);
  
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
