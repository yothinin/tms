#include <gtk/gtk.h>

typedef struct _MyWidgets {
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *lblCode, *lblName;
  GtkWidget *entCode, *entName;
  GtkWidget *btnSave, *btnExit;  
} MyWidgets;

static void btnSaveClicked (GtkWidget *widget, gpointer userdata){
  MyWidgets *w = (MyWidgets*) userdata;
  g_print ("code: %s, name: %s\n", gtk_entry_get_text (GTK_ENTRY(w->entCode)), gtk_entry_get_text (GTK_ENTRY(w->entName)));
}

int main (int argc, char *argv[]){
  MyWidgets w;

  gtk_init (&argc, &argv);

  w.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW(w.window), "Use struct to carry the widgets");
  gtk_window_set_position (GTK_WINDOW (w.window), GTK_ALIGN_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (w.window), 400, 200);
  gtk_container_set_border_width (GTK_CONTAINER (w.window), 10);

  w.vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (w.window), w.vbox);

  w.hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start (GTK_BOX (w.vbox), w.hbox, FALSE, FALSE, 5);

  w.lblCode = gtk_label_new ("Code");
  gtk_label_set_width_chars (GTK_LABEL(w.lblCode), 6);
  gtk_box_pack_start (GTK_BOX (w.hbox), w.lblCode, FALSE, FALSE, 5);
  gtk_label_set_xalign (GTK_LABEL (w.lblCode), 0);
  w.entCode = gtk_entry_new ();
  gtk_entry_set_width_chars (GTK_ENTRY (w.entCode), 14);
  gtk_entry_set_max_length (GTK_ENTRY (w.entCode), 13);
  gtk_box_pack_start (GTK_BOX (w.hbox), w.entCode, FALSE, FALSE, 5);

  w.hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start (GTK_BOX (w.vbox), w.hbox, FALSE, FALSE, 5);
  w.lblName = gtk_label_new ("Name");
  gtk_label_set_xalign (GTK_LABEL (w.lblName), 0);
  gtk_label_set_width_chars (GTK_LABEL (w.lblName), 6);
  gtk_box_pack_start (GTK_BOX (w.hbox), w.lblName, FALSE, FALSE, 5);
  w.entName = gtk_entry_new ();
  gtk_entry_set_max_length (GTK_ENTRY (w.entName), 20);
  gtk_entry_set_width_chars (GTK_ENTRY (w.entName), 21);
  gtk_box_pack_start (GTK_BOX (w.hbox), w.entName, FALSE, FALSE, 5);

  w.hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_end (GTK_BOX (w.vbox), w.hbox, FALSE, FALSE, 5);
  w.btnSave = gtk_button_new_with_label ("Save");
  w.btnExit = gtk_button_new_with_label ("Exit");
  gtk_box_pack_end (GTK_BOX (w.hbox), w.btnExit, FALSE, FALSE, 5);
  gtk_box_pack_end (GTK_BOX (w.hbox), w.btnSave, FALSE, FALSE, 5);

  g_signal_connect (w.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (w.btnSave, "clicked", G_CALLBACK (btnSaveClicked), &w);
  g_signal_connect (w.btnExit, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  gtk_widget_show_all (w.window);

  gtk_main ();

  return 0;
}
