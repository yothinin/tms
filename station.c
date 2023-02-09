#include <gtk/gtk.h>

typedef struct _MyObjects{
  GtkWidget *treeview;
	GtkWidget *entStaCode; 
	GtkWidget *entStaName;
	GtkWidget *btnSave;
  GtkWidget *btnDelete;
  GtkWidget *btnExit;
  GtkWidget *btnNew;
}MyObjects;

//static gboolean entStaCode_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
  //MyObjects *mobj = (MyObjects*) user_data;
  //const gchar *stacode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));

  //if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      //strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){
    //const gchar *stacode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
    ////g_print ("%s\n", stacode);

    //if (strlen(stacode) != 0){
      //gtk_widget_set_sensitive (mobj->entStaName, TRUE);
      //gtk_widget_grab_focus (mobj->entStaName);
    //}else{
      //gtk_widget_set_sensitive (mobj->entStaName, FALSE);    
    //}
    
    //return TRUE;
  //}
  
  //return FALSE;
//}

static gboolean entStaCode_release (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
  MyObjects *mobj = (MyObjects*) userdata;
  const gchar *stacode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  if (strcmp(gdk_keyval_name(event->keyval), "Return") == 0  ||
      strcmp(gdk_keyval_name(event->keyval), "KP_Enter") == 0){

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
}

static void btnSave_clicked (GtkWidget *widget, gpointer user_data){
  MyObjects *mobj = (MyObjects*) user_data;
  const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (staCode[0] != '\0' && staName[0] != '\0')
    g_print ("Save -> Code: %s, Name: %s\n", staCode, staName);
}

static void btnDelete_clicked (GtkWidget *widget, gpointer user_data){
  MyObjects *mobj = (MyObjects*) user_data;
  const gchar *staCode = gtk_entry_get_text (GTK_ENTRY(mobj->entStaCode));
  const gchar *staName = gtk_entry_get_text (GTK_ENTRY(mobj->entStaName));
  if (staCode[0] != '\0')
    g_print ("Delete -> Code: %s\n", staCode);
}

void rowChanged (GtkWidget *treeView, gpointer userdata) {
  MyObjects *mobj = (MyObjects*) userdata;
 
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(mobj->treeview));
  GtkTreeIter iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(mobj->treeview));
  if (gtk_tree_selection_get_selected(selection, &model, &iter)){
    const gchar *staCode, *staName;
    gtk_tree_model_get (model, &iter, 0, &staCode, 1, &staName, -1);
    gtk_entry_set_text (GTK_ENTRY(mobj->entStaCode), staCode);
    gtk_entry_set_text (GTK_ENTRY(mobj->entStaName), staName);
    gtk_widget_set_sensitive (mobj->entStaCode, FALSE);
    gtk_widget_set_sensitive (mobj->entStaName, TRUE);
    gtk_button_set_label (GTK_BUTTON(mobj->btnSave), "แก้ไข");
    gtk_widget_set_sensitive (mobj->btnSave, TRUE);
    gtk_widget_set_sensitive (mobj->btnDelete, TRUE);
  }
}

static void activate(GtkApplication* app, MyObjects mobj, gpointer user_data)
{
  GtkBuilder *builder;
  GtkWidget *window;
	GtkWidget *vbox;

  builder = gtk_builder_new_from_file("tms_station.glade");
  //gtk_builder_connect_signals(builder, NULL);

  window = (GtkWidget*)gtk_builder_get_object(builder, "window");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WINDOW_TOPLEVEL);
  gtk_window_set_gravity (GTK_WINDOW(window), GDK_GRAVITY_CENTER);

  mobj.treeview = (GtkWidget*) gtk_builder_get_object (builder, "treeView");
  mobj.entStaCode = (GtkWidget*) gtk_builder_get_object (builder, "entStaCode");
  mobj.entStaName = (GtkWidget*) gtk_builder_get_object (builder, "entStaName");
  mobj.btnSave = (GtkWidget*) gtk_builder_get_object (builder, "btnSave");
  mobj.btnDelete = (GtkWidget*) gtk_builder_get_object (builder, "btnDelete");
  mobj.btnExit = (GtkWidget*) gtk_builder_get_object (builder, "btnExit");
  mobj.btnNew = (GtkWidget*) gtk_builder_get_object (builder, "btnNew");
  GtkListStore *liststore = (GtkListStore*) gtk_builder_get_object (builder, "mainStore");
  
  g_signal_connect (mobj.btnNew, "clicked", G_CALLBACK (btnNewClicked), &mobj);
  //g_signal_connect (mobj.entStaCode, "key-press-event", G_CALLBACK (entStaCode_press), &mobj);
  //g_signal_connect (mobj.entStaName, "key-press-event", G_CALLBACK (entStaName_press), &mobj);
  g_signal_connect (mobj.entStaCode, "key-release-event", G_CALLBACK (entStaCode_release), &mobj);
  g_signal_connect (mobj.entStaName, "key-release-event", G_CALLBACK (entStaName_release), &mobj);
  g_signal_connect (mobj.btnSave, "clicked", G_CALLBACK (btnSave_clicked), &mobj);
  g_signal_connect (mobj.btnDelete, "clicked", G_CALLBACK (btnDelete_clicked), &mobj);
  g_signal_connect (mobj.treeview, "cursor-changed", G_CALLBACK (rowChanged), &mobj);
  g_signal_connect (mobj.btnExit, "clicked", G_CALLBACK (btnExit_clicked), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (btnExit_clicked), NULL);
  
  gtk_widget_grab_focus (mobj.btnNew);

  gtk_widget_show_all (window);

  gtk_main();
}

int main (int argc, char *argv[]){

	GtkApplication *app;
	int status = 0;
	/* Initialize the environment */
	app = gtk_application_new("pimpanya.com", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref (app);

  return status;
}
