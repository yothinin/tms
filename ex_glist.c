#include <stdio.h>
#include <glib.h>

void print_integer(gpointer data, gpointer user_data) {
    int value = GPOINTER_TO_INT(data);
    printf("%d\n", value);
}

void print_string(gpointer data, gpointer user_data) {
    //int value = GPOINTER_TO_INT(data);
    printf("%s\n", data);
}


int main(void) {
    // Initialize two GLists, one for strings and one for integers
    GList *string_list = NULL, *number_list = NULL;

    // Add some strings to the string_list using g_list_append
    string_list = g_list_append(string_list, "first");
    string_list = g_list_append(string_list, "second");
    string_list = g_list_append(string_list, "third");

    // Add some integers to the number_list using g_list_append and GINT_TO_POINTER
    number_list = g_list_append(number_list, GINT_TO_POINTER(27));
    number_list = g_list_append(number_list, GINT_TO_POINTER(14));
    number_list = g_list_append(number_list, GINT_TO_POINTER(42));

    // Print out the strings in the string_list using g_list_foreach and printf
    printf("Strings in the string_list:\n");
    //g_list_foreach(string_list, (GFunc)printf, "%s\n");
    g_list_foreach (string_list, (GFunc)print_string, NULL);

    // Print out the integers in the number_list using g_list_foreach and printf
    printf("\nIntegers in the number_list:\n");
    g_list_foreach(number_list, (GFunc)print_integer, NULL);

    // Free the memory used by the GLists using g_list_free
    g_list_free(string_list);
    g_list_free(number_list);

    return 0;
}
