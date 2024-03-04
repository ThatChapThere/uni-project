// Credit:
// https://
// gnome.pages.gitlab.gnome.org/gtkmm-documentation/chapter-drawingarea.html
#include "window.h"
#include <iostream>

Window::Window()
{
	add_action("screenshot", sigc::mem_fun(*this, &Window::screenshot));
	set_child(ga);
	set_child(ga2);
}

void Window::screenshot() {
	std::cout << "menu item clicked" << std::endl;
}

Window::~Window()
{
}
