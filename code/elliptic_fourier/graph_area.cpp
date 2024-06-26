#include <cairomm/context.h>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <iostream>
#include "graph_area.h"
#include "elliptic_fourier_analyser.h"
#include "elliptic_fourier_curve.h"

// temporary include
#include "csv_to_coord_set.h"

using namespace std;

GraphArea::GraphArea()
{
	set_draw_func(sigc::mem_fun(*this, &GraphArea::draw));
}

GraphArea::~GraphArea()
{
}

// This is a method of an area and the only information
// we have about said area is its width and height
void GraphArea::draw(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height
) {
	vector<array<double, 2>> coords =
		csv_to_coord_set("../contour/csv/obcordate.csv", -0.9, 0.9);
	//{{0, 0}, {1,1}, {0,1}};
	cr->set_source_rgb(0, 0, 0); // black
	draw_discrete(cr, width, height, coords);
	EllipticFourierAnalyser analyser(coords);
	for(int i = 1; i <= 10; i++)
	{
		auto curve = analyser.analyse(i);
		auto curve_shape = curve.get_shape(1000);
		cr->set_source_rgba(0, 0, 1, 1.f/(11-i)); // blue
		draw_continuous(cr, width, height, curve_shape);
	}
}

void GraphArea::draw_discrete(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height,
	vector<array<double, 2>> coords
) {
	int cx = width / 2;
	int cy = height / 2;
	int r = min(width, height) / 2;
	cr->move_to(cx + coords[0][0] * r, cy + coords[0][1] * r);
	double x, y;
	for(int i = 0; i < coords.size(); i++) {
		x = coords[i][0];
		y = coords[i][1];
		cr->line_to(cx + x * r, cy + y * r);
	}
	cr->line_to(cx + coords[0][0] * r, cy + coords[0][1] * r);
	cr->stroke();
	//cr->set_source_rgb(1, 0.5, 0); // orange
	/*
	for(int i = 0; i < coords.size(); i++) {
		x = coords[i][0];
		y = coords[i][1];
		cr->arc(cx + x * r, cy + y * r, 10,
				0, 2 * pi);
		cr->fill();
	}
	*/
}

void GraphArea::draw_continuous(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height,
	vector<array<double, 2>> coords
) {
	int cx = width / 2;
	int cy = height / 2;
	int r = min(width, height) / 2;
	cr->move_to(cx + coords[0][0] * r, cy + coords[0][1] * r);
	double x, y;
	for(int i = 1; i < coords.size(); i++) {
		x = coords[i][0];
		y = coords[i][1];
		if(isnan(x) || isnan(y)) continue;
		cr->line_to(cx + x * r, cy + y * r);
	}
	cr->stroke();
}
