#pragma once

#include <vector>
#include <array>

class EllipticFourierCurve
{
public:
	EllipticFourierCurve(
		std::vector<double> a,
		std::vector<double> b,
		std::vector<double> c,
		std::vector<double> d,
		double A,
		double C,
		double T
	);
	~EllipticFourierCurve();
	std::vector<std::array<double, 2>> get_shape(int resolution);
protected:
	std::vector<double> a;
	std::vector<double> b;
	std::vector<double> c;
	std::vector<double> d;
	double A;
	double C;
	double T;
	double N;
};
