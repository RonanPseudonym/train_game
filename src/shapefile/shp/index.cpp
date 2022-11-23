#include "../index.hpp"
#include <iostream>

Shapefile::Shp::Index::Index() {}

void Shapefile::Shp::Index::Parse(std::ifstream& _file) {
    header = Shapefile::General::Header();
    header.Parse(_file);

    while (_file.tellg() / 2 != (header.file_length)) {
        switch (header.shape_type) {
            case Shapefile::General::POINT: {
                Shapefile::Shp::Shape::Point* ptr = new Shapefile::Shp::Shape::Point();
                records.push_back(ptr);
            }
            case Shapefile::General::POLYGON: {
                Shapefile::Shp::Shape::Polygon* ptr = new Shapefile::Shp::Shape::Polygon();
                records.push_back(ptr);
            }
        }

        records[records.size() - 1]->Parse(_file);
    }
}