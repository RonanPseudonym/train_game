#include <iostream>
#include "shapefile/index.hpp"

int main() {
	Shapefile::Parser parser("data/maps/countries/World_Countries");

	parser.Load();
    parser.Parse();
}