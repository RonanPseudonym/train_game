#include "index.hpp"
#include <iostream>

Shapefile::Parser::Parser(std::string _path) {
	path = _path;
}

void Shapefile::Parser::Load() {
	shp_f.open(path + ".shp", std::ios::in | std::ios::binary);
    shp = Shapefile::Shp::Index();
    if (!shp_f.is_open()) Utils::UI::Error("Unable to open .shp file at " + path + ".shp", 4);

	shx_f.open(path + ".shx", std::ios::in | std::ios::binary);
    if (!shp_f.is_open()) Utils::UI::Error("Unable to open .shx file at " + path + ".shx", 5);

	dbf_f.open(path + ".dbf", std::ios::in | std::ios::binary);
    if (!shp_f.is_open()) Utils::UI::Error("Unable to open .dbf file at " + path + ".dbf", 6);
}

void Shapefile::Parser::Parse() {
    shp.Parse(shp_f);
}