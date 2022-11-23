#include "../../index.hpp"

/*
	Position |    Field   | Value |  Type   | Number | Order

	Byte 0   | Shape Type | 1     | Integer | 1      | Little
	Byte 4   | X          | X     | Double  | 1      | Little
	Byte 12  | Y          | Y     | Double  | 1      | Little
*/

Shapefile::Dbf::Header::FieldDescriptor::FieldDescriptor() {

}

void Shapefile::Dbf::Header::FieldDescriptor::Parse(std::ifstream& _file) {
	
}