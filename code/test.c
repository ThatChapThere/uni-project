/* Credit: https://www.gtk.org/docs/getting-started/hello-world */
#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello, World!");
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *button;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	button = gtk_button_new_with_label("Hello, World!");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
	gtk_window_set_child(GTK_WINDOW(window), button);

	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	/* create a gtk_application object
	 * this object is the application itself 
	 * we give it a very basic name and then set some flags
	 * for simplicity the default flags are used */
	app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	/* this connects the signal signified by the string "activate" with the function "activate"
	 * G_CALLBACK takes in a function pointer and makes it usable by the application object */
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	/* G_APPLICATION is analogous to G_CALLBACK
	 * it takes in application pointers instead of function pointers */
	status = g_application_run(G_APPLICATION(app), argc, argv);
	/* don't forget to deref! */
	g_object_unref(app);

	return status;
}
