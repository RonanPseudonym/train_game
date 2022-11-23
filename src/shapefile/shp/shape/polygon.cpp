#include "../../index.hpp"
#include "../../../config.hpp"

#include <iostream>

/* 
	TODO: NAN in doubles may be from issue with signed numbers. Look more into it tomororw
*/

/*
	Position |   Field    |   Value   |  Type   |   Number  | Order

	Byte 0   | Shape Type | 5         | Integer | 1         | Little
	Byte 4   | Box        | Box       | Double  | 4         | Little
	Byte 36  | NumParts   | NumParts  | Integer | 1         | Little
	Byte 40  | NumPoints  | NumPoints | Integer | 1         | Little
	Byte 44  | Parts      | Parts     | Integer | NumParts  | Little
	Byte X   | Points     | Points    | Point   | NumPoints | Little

	Note: X = 44 + 4 * NumParts
*/

void Shapefile::Shp::Shape::Polygon::Parse(std::ifstream& _file) {
	record_number  = Utils::Bitwise::IfstreamToBigEndianInt(_file);
	content_length = Utils::Bitwise::IfstreamToBigEndianInt(_file);

	int type = Utils::Bitwise::IfstreamToLittleEndianInt(_file);
	if (type != static_cast<int>(Shapefile::General::POLYGON)) {
		Utils::UI::Error("The currently parsing shapefile document is of a 'Polygon' type, but this record reads as not a Polygon (bytes 0-4 should be 5, but instead are " + std::to_string(type) + ")", 3);
	}

	bounding_box = {
		Utils::Bitwise::IfstreamToLittleEndianDouble(_file), 
		Utils::Bitwise::IfstreamToLittleEndianDouble(_file), 
		Utils::Bitwise::IfstreamToLittleEndianDouble(_file), 
		Utils::Bitwise::IfstreamToLittleEndianDouble(_file)
	};

	num_parts  = Utils::Bitwise::IfstreamToLittleEndianInt(_file);
	num_points = Utils::Bitwise::IfstreamToLittleEndianInt(_file);

	for (int i = 0; i < num_parts; i ++) {
		parts.push_back(Utils::Bitwise::IfstreamToLittleEndianInt(_file));
	}

	for (int i = 0; i < num_points; i ++) {
		points.push_back({ 
			Utils::Bitwise::IfstreamToLittleEndianDouble(_file),
			Utils::Bitwise::IfstreamToLittleEndianDouble(_file)
		});
	}

	#ifdef DEBUG_TEXT

	std::cout << std::endl;
	Utils::UI::Note(Utils::UI::Color::Compile(Utils::UI::Color::BOLD)+"New Record");
	Utils::UI::Note("Record Number:  " + std::to_string(record_number));
	Utils::UI::Note("Content Length: " + std::to_string(content_length));
	Utils::UI::Note(
		static_cast<std::string>("Bounding Box:") +
		"\n\tX Minimum: " + std::to_string(bounding_box.x_min) +
		"\n\tX Maximum: " + std::to_string(bounding_box.x_max) +
		"\n\tY Minimum: " + std::to_string(bounding_box.y_min) +
		"\n\tY Maximum: " + std::to_string(bounding_box.y_max)
	);

	#ifdef DEBUG_PRINT_PARTS

	Utils::UI::Note("Parts:");
	for (int i = 0; i < parts.size(); i ++) {
		Utils::UI::Note("\t" + std::to_string(parts[i]));
	}

	#endif

	#ifdef DEBUG_PRINT_POINTS

	Utils::UI::Note("Points:");
	for (int i = 0; i < parts.size(); i ++) {
		Utils::UI::Note("\t" + std::to_string(points[i].x) + " " + std::to_string(points[i].y));
	}

	#endif

	#endif
}