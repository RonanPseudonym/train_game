#include <iostream>
#include "shapefile/index.hpp"

int main() {
	Shapefile::Parser parser("data/maps/gadm41_GBR_shp/gadm41_GBR_3");

	parser.Load();
    parser.Parse();
}
