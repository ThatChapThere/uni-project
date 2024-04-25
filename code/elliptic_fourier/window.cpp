// Credit:
// https://
// gnome.pages.gitlab.gnome.org/gtkmm-documentation/chapter-drawingarea.html
#include "window.h"
#include <iostream>

Window::Window()
:test_button("click me!")
{
	ga.set_hexpand(true);
	test_box.append(test_button);
	test_box.prepend(ga);
	set_child(test_box);
}

Window::~Window()
{
}
