#ifndef ELLIPTIC_FOURIER_H
#define ELLIPTIC_FOURIER_H

#include <gtkmm/window.h>
#include "drawing_area.h"

class EllipticFourier: public Gtk::Window
{
public:
	EllipticFourier();
	~EllipticFourier() override;
protected:
	GraphArea ga;
};

#endif
