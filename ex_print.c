#include <gtk/gtk.h>
#include <gtk/gtkprintcontext.h>

static void
print_hello (GtkPrintOperation *operation,
             GtkPrintContext   *context,
             gpointer           user_data)
{
  PangoLayout *layout;
  layout = gtk_print_context_create_pango_layout (context);
  
  g_print ("hello_print\n");

  pango_layout_set_text (layout, "Hello, world!\nThis is print to pdf file.", -1);

  GtkPageSetup *page_setup = gtk_print_context_get_page_setup (context);
  gdouble width = gtk_page_setup_get_page_width (page_setup, GTK_UNIT_POINTS);
  gdouble height = gtk_page_setup_get_page_height (page_setup, GTK_UNIT_POINTS);

  cairo_t *cr;
  cr = gtk_print_context_get_cairo_context (context);

  //gtk_render_layout (gtk_print_context_get_style (context), cr, 0, 0, layout);
  //gtk_render_layout (GTK_STYLE_CONTEXT (context), cr, 0, 0, layout);
  //gtk_render_layout (gtk_print_context_get_style (context), cr, 0, 0, layout);
  GtkStyleContext *style_context;
  style_context = gtk_style_context_new();
  gtk_render_layout (style_context, cr, 0, 0, layout);

  g_object_unref (layout);
}

static void
print_cb (GtkButton *button,
          gpointer   user_data)
{
  GtkPrintOperation *print;
  print = gtk_print_operation_new ();

  g_signal_connect (print, "draw_page",
                    G_CALLBACK (print_hello), NULL);

  //gtk_print_operation_set_export_filename (print, "hello.pdf");

  GtkPrintOperationResult res;
  res = gtk_print_operation_run (print,
                                 GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG, 
                                 //GTK_PRINT_OPERATION_ACTION_EXPORT,
                                 GTK_WINDOW (user_data),
                                 NULL);
  g_print ("%d\n", res);

  if (res == GTK_PRINT_OPERATION_RESULT_ERROR)
    {
      GError *error = NULL;
      gtk_print_operation_get_error (print, &error);
      g_printerr ("Error printing file: %s\n", error->message);
      g_error_free (error);    
    }
  else if (res == GTK_PRINT_OPERATION_RESULT_CANCEL)
    {

    }

  g_object_unref (print);
}


int
main (int   argc,
      char *argv[])
{
  GtkWidget *window, *button;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_button_new_with_label ("Print");
  g_signal_connect (button, "clicked",
                    G_CALLBACK (print_cb), window);
  gtk_container_add (GTK_CONTAINER (window), button);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
