#ifndef GRAPH_AREA_H
#define GRAPH_AREA_H

#include <gtkmm/drawingarea.h>

// GraphArea is a custom class that inherits from DrawingArea
// It has custom methods 
// The draw method is also a custom method, not an inhereted one. It has to me manually assigned as
// the drawing function in the contstuctor.
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
