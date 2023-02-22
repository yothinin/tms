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

#endif //FUNCTIONS_H
