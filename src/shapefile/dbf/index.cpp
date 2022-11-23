#include "../index.hpp"
#include <iostream>

Shapefile::Dbf::Index::Index() {

}

void Shapefile::Dbf::Index::Parse(std::ifstream& _file) {
    header = Shapefile::Dbf::Header::Index();
    header.Parse(_file);
}