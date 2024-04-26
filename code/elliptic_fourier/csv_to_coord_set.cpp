#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include "csv_to_coord_set.h"

using namespace std;

vector<array<double, 2>> csv_to_coord_set(
	string filename,
	double min_coord,
	double max_coord
) {
	vector<array<double, 2>> result;
	ifstream f(filename);
	string s;
	double x, y,
	       min_found = numeric_limits<double>::max(),
	       max_found = numeric_limits<double>::lowest();
	// Turn coordinates into doubles
	// and find minimum and maximum values
	int counter = 0;
	while(getline(f, s))
	{
		if(counter++ % 10) continue;
		int comma_position = s.find(',');
		y = stod(s.substr(0, comma_position));
		x = stod(s.substr(   comma_position + 1, string::npos));
		result.push_back({x, y});
		min_found = min({min_found, x, y});
		max_found = max({max_found, x, y});
	}
	double range_coord = max_coord - min_coord;
	double range_found = max_found - min_found;
	// found * mult = coord
	double found_to_coord_multiplier = range_coord / range_found;
	for(array<double, 2> &coord: result)
	{
		// centre minima around 0
		coord[0] -= min_found;
		coord[1] -= min_found;
		// multiply
		coord[0] *= found_to_coord_multiplier;
		coord[1] *= found_to_coord_multiplier;
		// correct minima
		coord[0] += min_coord;
		coord[1] += min_coord;
	}
	return result;
}
