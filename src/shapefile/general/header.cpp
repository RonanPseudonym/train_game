#include "../index.hpp"
#include "../../config.hpp"
#include <iostream>

Shapefile::General::Header::Header() {}

void Shapefile::General::Header::Parse(std::ifstream& _file) {
	/*       
		Position |     Field    |    Value    |  Type   | Order

		Byte 0   | File Code    | 9994        | Integer | Big
		Byte 4   | Unused       | 0           | Integer | Big
		Byte 8   | Unused       | 0           | Integer | Big
		Byte 12  | Unused       | 0           | Integer | Big
		Byte 16  | Unused       | 0           | Integer | Big
		Byte 20  | Unused       | 0           | Integer | Big
		Byte 24  | File Length  | File Length | Integer | Big
		Byte 28  | Version      | 1000        | Integer | Little
		Byte 32  | Shape Type   | Shape Type  | Integer | Little
		Byte 36  | Bounding Box | Xmin        | Double  | Little
		Byte 44  | Bounding Box | Ymin        | Double  | Little
		Byte 52  | Bounding Box | Xmax        | Double  | Little
		Byte 60  | Bounding Box | Ymax        | Double  | Little
		Byte 68* | Bounding Box | Zmin        | Double  | Little
		Byte 76* | Bounding Box | Zmax        | Double  | Little
		Byte 84* | Bounding Box | Mmin        | Double  | Little
		Byte 92* | Bounding Box | Mmax        | Double  | Little
	*/

	/*
		Value | Shape Type

		0     | Null Shape
		1     | Point
		3     | PolyLine
		5     | Polygon
		8     | MultiPoint
		11    | PointZ
		13    | PolyLineZ
		15    | PolygonZ
		18    | MultiPointZ
		21    | PointM
		23    | PolyLineM
		25    | PolygonM
		28    | MultiPointM
		31    | MultiPatch
	*/

	if (Utils::Bitwise::IfstreamToBigEndianInt(_file) != 9994) {
		Utils::UI::Error("First 4 bytes of currently opened shapefile must be 9994, encoded as a big-endian integer", 2);
	}

	_file.seekg(4 * 5, std::ios::cur);

	file_length = Utils::Bitwise::IfstreamToBigEndianInt      (_file);
	version     = Utils::Bitwise::IfstreamToLittleEndianInt   (_file);

	switch (Utils::Bitwise::IfstreamToLittleEndianInt(_file)) {
		case 1: shape_type = Shapefile::General::POINT;
		case 5: shape_type = Shapefile::General::POLYGON;
	}

	bounding_box = {0, 0, 0, 0};

	bounding_box.x_min = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);
	bounding_box.x_max = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);
	bounding_box.y_min = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);
	bounding_box.y_max = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);

	#ifdef DEBUG_TEXT

	Utils::UI::Note("File Length: " + std::to_string(file_length));
	Utils::UI::Note("Version:     " + std::to_string(version));
	Utils::UI::Note("Shape Type:  " + std::to_string(static_cast<int>(shape_type)));
	Utils::UI::Note("X Minimum:   " + std::to_string(bounding_box.x_min));
	Utils::UI::Note("X Maximum:   " + std::to_string(bounding_box.x_max));
	Utils::UI::Note("Y Minimum:   " + std::to_string(bounding_box.y_min));
	Utils::UI::Note("Y Maximum:   " + std::to_string(bounding_box.y_max));

	#endif

	_file.seekg(8 * 4, std::ios::cur);
}
