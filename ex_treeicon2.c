#include <gtk/gtk.h>

static void on_icon_view_item_activated(GtkIconView *icon_view, GtkTreePath *path, gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Get the model and iter of the selected item
    model = gtk_icon_view_get_model(icon_view);
    gtk_tree_model_get_iter(model, &iter, path);

    // Get the text of the selected item
    gchar *text;
    gtk_tree_model_get(model, &iter, 1, &text, -1);

    // Call the corresponding function based on the selected item
    if (g_strcmp0(text, "เส้นทาง") == 0) {
        system("./route");
    } else if (g_strcmp0(text, "สถานี") == 0) {
        system("./station");
    } else if (g_strcmp0(text, "ประเภทรถ") == 0) {
        system("./bus");
    } else if (g_strcmp0(text, "ตารางเดินรถ") == 0) {
        system("./schedule");
    } else if (g_strcmp0(text, "จำหน่ายตั๋ว") == 0) {
        system("./ticket");
    } else if (g_strcmp0(text, "รายงาน") == 0) {
        system("./report");
    }

    // Free the memory allocated for text
    g_free(text);
}


//static void on_icon_view_item_activated(GtkIconView *icon_view, GtkTreePath *path, gpointer user_data) {
    //GtkTreeModel *model;
    //GtkTreeIter iter;

    //// Get the model and iter of the selected item
    //model = gtk_icon_view_get_model(icon_view);
    //gtk_tree_model_get_iter(model, &iter, path);

    //// Get the text of the selected item
    //gchar *text;
    //gtk_tree_model_get(model, &iter, 1, &text, -1);

    //// Display a message box with the text of the selected item
    //gchar *message = g_strdup_printf("You double-clicked %s", text);
    //GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
    //gtk_dialog_run(GTK_DIALOG(dialog));
    //gtk_widget_destroy(dialog);
    //g_free(message);
    //g_free(text);
//}

static void on_window_closed(GtkWidget *widget, gpointer user_data) {
    // Exit the main loop when the window is closed
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    // Initialize Gtk
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ระบบงานจำหน่ายตั๋วโดยสาร");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Create three pixbufs from image files
    GdkPixbuf *route_pixbuf = gdk_pixbuf_new_from_file("icons/route.png", NULL);
    GdkPixbuf *station_pixbuf = gdk_pixbuf_new_from_file("icons/station.png", NULL);
    GdkPixbuf *bus_pixbuf = gdk_pixbuf_new_from_file("icons/bus.png", NULL);
    GdkPixbuf *schedule_pixbuf = gdk_pixbuf_new_from_file("icons/schedule.png", NULL);
    GdkPixbuf *ticket_pixbuf = gdk_pixbuf_new_from_file("icons/ticket.png", NULL);
    GdkPixbuf *printer_pixbuf = gdk_pixbuf_new_from_file("icons/printer.png", NULL);

    // Create a tree store to hold the icon data
    GtkTreeStore *store = gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
    GtkTreeIter iter;

    // Add the Route icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, route_pixbuf, 1, "เส้นทาง", -1);

    // Add the Station icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, station_pixbuf, 1, "สถานี", -1);

    // Add the Schedule icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, bus_pixbuf, 1, "ประเภทรถ", -1);

    // Add the Schedule icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, schedule_pixbuf, 1, "ตารางเดินรถ", -1);

    // Add the Schedule icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, ticket_pixbuf, 1, "จำหน่ายตั๋ว", -1);

    // Add the Schedule icon
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 0, printer_pixbuf, 1, "รายงาน", -1);

    // Create a new icon view widget
    GtkWidget *icon_view = gtk_icon_view_new();
    gtk_container_add(GTK_CONTAINER(window), icon_view);

    // Set the icon view's model to the tree store
    gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view), GTK_TREE_MODEL(store));
    g_object_unref(store);

    // Set the icon view's properties
    gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view), 1);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view), 0);

    // Connect the signals
    g_signal_connect(icon_view, "item-activated", G_CALLBACK(on_icon_view_item_activated), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    // Show the window and
gtk_widget_show_all(window);

// Start the main loop
gtk_main();

return 0;
}
