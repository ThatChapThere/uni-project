#include <cairomm/context.h>
#include <cmath>
#include "drawing_area.h"

using std::sin;

GraphArea::GraphArea()
{
	set_draw_func(sigc::mem_fun(*this, &GraphArea::draw));
}

GraphArea::~GraphArea()
{
}

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
	cr->stroke();
}

double GraphArea::waveform(double x)
{
	double y = 0;
	double freqs[] = {1, 1.1, 0.8};
	double mags[] = {1, 1.1, 0.8};

	for(int i = 0; i < sizeof(freqs)/sizeof(freqs[0]); i++)
	{
		y += sin(x * freqs[i]) * mags[i];
	}

	return y;
}
