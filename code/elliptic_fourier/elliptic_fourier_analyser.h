#pragma once

#include <vector>
#include <array>
#include "elliptic_fourier_curve.h"

class EllipticFourierAnalyser
{
public:
	EllipticFourierAnalyser(std::vector<std::array<double, 2>> points);
	~EllipticFourierAnalyser();
	EllipticFourierCurve analyse(unsigned int coefficient_count);
protected:
	double T;
	int K;
	std::vector<double> x, y, t, dx, dy, dt;
	void calculate_deltas();
	double centre(std::vector<double> coord, std::vector<double> dcoord);
	double coefficient(
		unsigned int n,
		std::vector<double> dcoord,
		double (*trig_function)(double)
	);
};
