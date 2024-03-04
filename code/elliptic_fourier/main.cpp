// Credit:
// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-helloworld.html
#include "window.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("com.thatchapthere.elliptic.fourier");

	return app->make_window_and_run<Window>(argc, argv);
}
