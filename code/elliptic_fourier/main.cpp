// Credit:
// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-helloworld.html
#include <gtkmm/application.h>
#include "window.h"
#include "csv_to_coord_set.h"

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("com.thatchapthere.elliptic.fourier");

	return app->make_window_and_run<Window>(argc, argv);
	csv_to_coord_set("../contour/csv/cordate.csv", -0.9, 0.9);
}
