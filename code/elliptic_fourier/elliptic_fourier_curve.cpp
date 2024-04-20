#include <cmath>
#include <iostream>
#include "elliptic_fourier_curve.h"

using std::numbers::pi;

EllipticFourierCurve::~EllipticFourierCurve()
{
}

EllipticFourierCurve::EllipticFourierCurve(
	std::vector<double> a,
	std::vector<double> b,
	std::vector<double> c,
	std::vector<double> d,
	double A,
	double C,
	double T
) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->C = C;
	this->T = T;
	N = a.size();
}

std::vector<std::array<double, 2>> EllipticFourierCurve::get_shape(int resolution)
{
	std::vector<std::array<double, 2>> shape;
	double x, y, t;
	for(int i = 0; i < resolution; i++)
	{
		t = T * i / resolution;
		x = A;
		y = C;
		for(int n = 1; n <= N; n++)
		{
			x += a[n - 1] * std::cos(2 * n * pi * t);
			x += b[n - 1] * std::sin(2 * n * pi * t);
			y += c[n - 1] * std::cos(2 * n * pi * t);
			y += d[n - 1] * std::sin(2 * n * pi * t);
		}
		std::array<double, 2> coord = {x, y};
		shape.push_back(coord);
	}
	return shape;
}
