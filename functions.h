/*
 * header for functions.c
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void change_keyb (gchar *new_group);
GtkTreeIter *get_iter (const gchar* str, gint col, int ext_condition, gpointer userdata);
void display_warning_message(const gchar *message);
void freeRoute(gpointer data);
void freeStation (gpointer data);
void searchCombo(GtkComboBox *combo_box, const gchar *text, GtkTreeIter *result);
gint find_combo_box_index(GtkComboBox *combo_box, const gchar *id);

#endif //FUNCTIONS_H
