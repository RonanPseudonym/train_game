#include "index.hpp"
#include <iostream>

Shapefile::Parser::Parser(std::string _path) {
	path = _path;
}

void Shapefile::Parser::Load() {
	shp_f.open(path + ".shp", std::ios::in | std::ios::binary);
    shp = Shapefile::Shp::Index();

	shx_f.open(path + ".shx", std::ios::in | std::ios::binary);

	dbf_f.open(path + ".dbf", std::ios::in | std::ios::binary);
}

void Shapefile::Parser::Parse() {
    shp.Parse(shp_f);
}