#include "../index.hpp"
#include <iostream>

Shapefile::Shx::Index::Index() {

}

void Shapefile::Shx::Index::Parse(std::ifstream& _file) {
    header = Shapefile::General::Header();
    header.Parse(_file);

    while (_file.tellg() / 2 != header.file_length) {
        records.push_back(Shapefile::Shx::IndexRecord());
        records[records.size() - 1].Parse(_file);
    }
}