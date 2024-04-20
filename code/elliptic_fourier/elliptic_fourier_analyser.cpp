#include <cmath>
#include <iostream>
#include "elliptic_fourier_analyser.h"

using std::numbers::pi;

EllipticFourierAnalyser::~EllipticFourierAnalyser()
{
}

EllipticFourierAnalyser::EllipticFourierAnalyser(std::vector<std::array<double, 2>> points)
{
	for(auto coord: points)
	{
		x.push_back(coord[0]);
		y.push_back(coord[1]);
	}
	K = points.size();
	t.resize(K);
	dx.resize(K);
	dy.resize(K);
	dt.resize(K);
	calculate_deltas();
}

EllipticFourierCurve EllipticFourierAnalyser::analyse(unsigned int N)
{
	std::vector<double> a, b, c, d;
	a.resize(N);
	b.resize(N);
	c.resize(N);
	d.resize(N);
	for(int n = 1; n <= N; n++)
	{
		a[n-1] = coefficient(n, dx, std::cos);
		b[n-1] = coefficient(n, dx, std::sin);
		c[n-1] = coefficient(n, dy, std::cos);
		d[n-1] = coefficient(n, dy, std::sin);
	}
	double A = centre(x, dx);
	double C = centre(y, dy);
	return EllipticFourierCurve(a, b, c, d, A, C, T);
}

void EllipticFourierAnalyser::calculate_deltas()
{
	for(int p = 0; p < K; p++)
	{
		int p_minus_one = p == 0 ? K - 1 : p - 1;
		dx[p] = x[p] - x[p_minus_one];
		dy[p] = y[p] - y[p_minus_one];
		dt[p] = sqrt(dx[p] * dx[p] + dy[p] * dy[p]);
		t[p] = dt[p];
		if(p != 0) t[p] += t[p-1];
	}
	T = t[K - 1];
}

double EllipticFourierAnalyser::coefficient(
	unsigned int n,
	std::vector<double> dcoord,
	double (*trig_function)(double)
) {
	double sum = 0;
	for(int p = 0; p < K; p++)
	{
		int p_minus_one = p == 0 ? K - 1 : p - 1;
		double t_p_minus_one = p == 0 ? 0 : t[p - 1];
		sum += (dcoord[p] / dt[p]) *
		       (trig_function(2 * n * pi * t[p] / T) -
		        trig_function(2 * n * pi * t_p_minus_one / T));
	}
	sum *= T / (2 * n * n * pi * pi);
	return sum;
}

double EllipticFourierAnalyser::centre(std::vector<double> coord, std::vector<double> dcoord)
{
	double sum = 0;
	double sum_xi_delta = 0;
	for(int p = 0; p < K; p++)
	{
		int p_minus_one = p == 0 ? K - 1 : p - 1;
		//double t_p_minus_one = t[p_minus_one];
		double t_p_minus_one = p == 0 ? 0 : t[p - 1];
		sum += ((dcoord[p] / (2 * dt[p]))) *
		       (t[p] * t[p] - t_p_minus_one * t_p_minus_one);
		double xi_delta = 0;
		/*
		for(int j = 0; j < p; j++)
		{
			xi_delta += dcoord[j];
			xi_delta -= (dcoord[p] / dt[p]) * dt[j];
		}
		*/
		xi_delta = coord[p_minus_one];
		xi_delta -= (dcoord[p] / dt[p]) * t_p_minus_one;
		sum_xi_delta += xi_delta * (t[p] - t_p_minus_one);
	}
	return (sum + sum_xi_delta) / T;
}
