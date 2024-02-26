// Credit:
// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-helloworld.html
#include "elliptic_fourier.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("Test Application");

	return app->make_window_and_run<EllipticFourier>(argc, argv);
}
