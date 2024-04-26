// Credit:
// https://
// gnome.pages.gitlab.gnome.org/gtkmm-documentation/chapter-drawingarea.html
#include "window.h"
#include <iostream>

Window::Window()
{
	set_child(ga);
}

Window::~Window()
{
}
