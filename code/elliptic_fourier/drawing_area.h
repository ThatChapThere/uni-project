#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <gtkmm/drawingarea.h>

class GraphArea: public Gtk::DrawingArea
{
public:
	GraphArea();
	virtual ~GraphArea();

protected:
	void draw(
		const Cairo::RefPtr<Cairo::Context>& cr,
		const int width,
		const int height
	);
	double waveform(double x);
};

#endif
