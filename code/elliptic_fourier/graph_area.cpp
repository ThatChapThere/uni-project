#include <cairomm/context.h>
#include <cmath>
#include <numbers>
#include <algorithm>
#include "graph_area.h"

using std::sin;
using std::cos;
using std::min;
using std::max;
using std::numbers::pi;

GraphArea::GraphArea()
{
	set_draw_func(sigc::mem_fun(*this, &GraphArea::draw));
}

GraphArea::~GraphArea()
{
}

// This is a method of an area and the only information
// we have about said area is it's width and height
void GraphArea::draw(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height
) {
	cr->set_source_rgb(0, 0, 0.5); // blue

	int i = 0;
	cr->move_to(i, height/2 + waveform(i/20.0) * height/4);
	for(i = 1; i <= width; i++)
	{
		cr->line_to(i, height/2 + waveform(i/20.0) * height/4);
	}
	//cr->fill();

	cr->begin_new_path();
	cr->set_source_rgb(0, 0, 0); // black
	double theta = 0;
	double main_radius = min(width, height) / 2;
	double radius;
	radius = main_radius/2 + (main_radius/2) * waveform(theta);
	cr->move_to(width/2 + radius*sin(theta), height/2 + radius*cos(theta));
	for(;theta <= 2 * pi; theta += 0.01)
	{
		radius = main_radius/2 + (main_radius/2) * waveform(theta);
		cr->line_to(width/2 + radius*sin(theta), height/2 + radius*cos(theta));
	}
	cr->fill();
}

// This is a waveform method that we can use generally to return a value based on an input
double GraphArea::waveform(double x)
{
	double y = 0;
	double freqs[] = {10, 4};
	double mags[] = {0.1, 0.14};

	for(int i = 0; i < sizeof(freqs)/sizeof(freqs[0]); i++)
	{
		y += sin(x * freqs[i]) * mags[i];
	}

	return y;
}
