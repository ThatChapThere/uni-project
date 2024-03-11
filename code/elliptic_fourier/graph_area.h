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
	double centre(
		double T,
		int32_t K,
		double xy[],
		double t[],
		double delta_xy[],
		double delta_t[]
	);
	double coefficient(
		int32_t n,
		double T,
		int32_t K,
		double xy[],
		double t[],
		double delta_xy[],
		double delta_t[],
		double (*trig_function)(double)
	);
	void draw_discrete(
		const Cairo::RefPtr<Cairo::Context>& cr,
		const int width,
		const int height,
		int32_t K,
		double x[],
		double y[]
	);
	void generate_functions(
		double x[], 
		double y[], 
		int32_t K,
		double t[], 
		double delta_x[], 
		double delta_y[],
		double delta_t[],
		double &T
	);
	void draw_continuous(
		const Cairo::RefPtr<Cairo::Context>& cr,
		const int width,
		const int height,
		int32_t K,
		double x[],
		double y[]
	);
};

#endif
