// Credit: https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/chapter-drawingarea.html
#include "elliptic_fourier.h"
#include <iostream>

EllipticFourier::EllipticFourier()
{
	set_child(ga);
}

EllipticFourier::~EllipticFourier()
{
}
