/*
 * header for functions.c
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
extern void change_keyb (gchar *new_group);
extern GtkTreeIter *get_iter (const gchar* str, gint col, int ext_condition, gpointer userdata);
#endif //FUNCTIONS_H
