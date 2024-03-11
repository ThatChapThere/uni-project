#include <cairomm/context.h>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <iostream>
#include "graph_area.h"

using std::sin;
using std::cos;
using std::min;
using std::max;
using std::numbers::pi;
using std::cout;
using std::endl;
using std::isnan;

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
	/*
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
	//cr->fill();
	*/
	double x[] = {-0.5, -0.5, 0.5, 0.5,  0.375, 0.375, 0.125,  0.125,    0};
	double y[] = {   0,  0.5, 0.5,   0, -0.125,  -0.5,  -0.5, -0.375, -0.5};
	int32_t K = sizeof(x) / sizeof(x[0]);
	draw_discrete(cr, width, height, K, x, y);
	double t[K];
	double delta_x[K];
	double delta_y[K];
	double delta_t[K];
	double T;
	generate_functions(x, y, K, t, delta_x, delta_y, delta_t, T);
	double centre_y = centre(T, K, y, t, delta_y, delta_t);
	//centre_y = -0.05;
	double centre_x = centre(T, K, x, t, delta_x, delta_t);
	int32_t N = 10;
	double a[N];
	double b[N];
	double c[N];
	double d[N];
	for(int32_t n = 0; n < N; n++)
	{
		a[n] = coefficient(n + 1, T, K, x, t, delta_x, delta_t, cos);
		b[n] = coefficient(n + 1, T, K, x, t, delta_x, delta_t, sin);
		c[n] = coefficient(n + 1, T, K, y, t, delta_y, delta_t, cos);
		d[n] = coefficient(n + 1, T, K, y, t, delta_y, delta_t, sin);
	}
	int32_t resolution = 1000;
	double transform_x[resolution];
	double transform_y[resolution];
	for(int32_t max_n = 1; max_n <= N; max_n++)
	{
		for(int32_t i = 0; i < resolution; i++)
		{
			double t_smooth = T * i / resolution;
			transform_x[i] = centre_x;
			transform_y[i] = centre_y;
			for(int32_t n = 1; n <= max_n; n++)
			{
				transform_x[i] += 
					a[n - 1] * cos(2 * n * pi * t_smooth);
				transform_x[i] +=
					b[n - 1] * sin(2 * n * pi * t_smooth);
				transform_y[i] +=
					c[n - 1] * cos(2 * n * pi * t_smooth);
				transform_y[i] +=
					d[n - 1] * sin(2 * n * pi * t_smooth);
			}
		}
		// blue
		cr->set_source_rgb(1 - (double)max_n/N, 1 - (double)max_n/N, 1);
		draw_continuous(cr, width, height, resolution, transform_x, transform_y);
	}
}

void GraphArea::generate_functions(
	double x[], 
	double y[], 
	int32_t K,
	double t[], 
	double delta_x[], 
	double delta_y[],
	double delta_t[],
	double &T
) {
	for(int32_t p = 0; p < K; p++)
	{
		int32_t p_minus_one = p == 0 ? K - 1 : p - 1;
		delta_x[p] = x[p] - x[p_minus_one];
		delta_y[p] = y[p] - y[p_minus_one];
		delta_t[p] = sqrt(delta_x[p] * delta_x[p] + delta_y[p] * delta_y[p]);
		t[p] = delta_t[p];
		if(p != 0)
		{
			t[p] += t[p-1];
		}
	}
	T = t[K - 1];
}

void GraphArea::draw_discrete(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height,
	int32_t K,
	double x[],
	double y[]
) {
	cr->set_source_rgb(0, 0, 0); // black
	int centre_x = width / 2;
	int centre_y = height / 2;
	int radius = min(width, height) / 2;
	cr->move_to(centre_x + x[0] * radius, centre_y + y[0] * radius);
	for(int32_t i = 0; i < K; i++) {
		cr->line_to(centre_x + x[i] * radius, centre_y + y[i] * radius);
	}
	cr->line_to(centre_x + x[0] * radius, centre_y + y[0] * radius);
	cr->stroke();
	cr->set_source_rgb(1, 0.5, 0); // orange
	for(int32_t i = 0; i < K; i++) {
		cr->arc(centre_x + x[i] * radius, centre_y + y[i] * radius, 10, 0,
		        2 * pi);
		cr->fill();
	}
}

void GraphArea::draw_continuous(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const int width,
	const int height,
	int32_t K,
	double x[],
	double y[]
) {
	int centre_x = width / 2;
	int centre_y = height / 2;
	int radius = min(width, height) / 2;
	/*
	cr->set_source_rgb(1, 1, 0); // yellow
	for(int32_t i = 0; i < K; i++) {
		cr->arc(centre_x + x[i] * radius, centre_y + y[i] * radius, 3, 0, 2 * pi);
		cr->fill();
	}
	*/
	cr->move_to(centre_x + x[0] * radius, centre_y + y[0] * radius);
	for(int32_t i = 0; i < K-1; i++) {
		if(isnan(x[i]) || isnan(y[i])) continue;
		if(isnan(x[i + 1]) || isnan(y[i + 1])) continue;
		cr->move_to(centre_x + x[i] * radius, centre_y + y[i] * radius);
		cr->line_to(centre_x + x[i + 1] * radius, centre_y + y[i + 1] * radius);
		cr->stroke();
	}
}

// This is a waveform method that we can use generally to return a value based on
// an input
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

double GraphArea::coefficient(
	int32_t n,
	double T,
	int32_t K,
	double xy[],
	double t[],
	double delta_xy[],
	double delta_t[],
	double (*trig_function)(double)
) {
	double sum = 0;
	for(int32_t p = 0; p < K; p++)
	{
		int32_t p_minus_one = p == 0 ? K - 1 : p - 1;
		double t_p_minus_one = p == 0 ? 0 : t[p - 1];
		sum += (delta_xy[p] / delta_t[p]) *
		       (trig_function(2 * n * pi * t[p] / T) -
		        trig_function(2 * n * pi * t_p_minus_one / T));
	}
	sum *= T / (2 * n * n * pi * pi);
	return sum;
}

double GraphArea::centre(
	double T,
	int32_t K,
	double xy[],
	double t[],
	double delta_xy[],
	double delta_t[]
) {
	double sum = 0;
	double sum_xi_delta = 0;
	for(int32_t p = 0; p < K; p++)
	{
		int32_t p_minus_one = p == 0 ? K - 1 : p - 1;
		//double t_p_minus_one = t[p_minus_one];
		double t_p_minus_one = p == 0 ? 0 : t[p - 1];
		sum += ((delta_xy[p] / (2 * delta_t[p]))) *
		       (t[p] * t[p] - t_p_minus_one * t_p_minus_one);
		double xi_delta = 0;
		/*
		for(int32_t j = 0; j < p; j++)
		{
			xi_delta += delta_xy[j];
			xi_delta -= (delta_xy[p] / delta_t[p]) * delta_t[j];
		}
		*/
		xi_delta = xy[p_minus_one];
		xi_delta -= (delta_xy[p] / delta_t[p]) * t_p_minus_one;
		sum_xi_delta += xi_delta * (t[p] - t_p_minus_one);
	}
	return (sum + sum_xi_delta) / T;
}
