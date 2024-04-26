#include <vector>
#include <array>
#include <string>

std::vector<std::array<double, 2>> csv_to_coord_set(
	std::string filename,
	double min_coord,
	double max_coord
);
