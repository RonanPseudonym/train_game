#include "../../index.hpp"
#include "../../../config.hpp"
#include <iostream>

Shapefile::Dbf::Header::Index::Index() {}

void Shapefile::Dbf::Header::Index::Parse(std::ifstream& _file) {
	/*
			     Byte         |    Contents   |  						Meaning

		0 	                  | 1 byte 	      | Valid dBASE for DOS file; bits 0–2 indicate version number, bit 3 indicates the presence of a dBASE for DOS memo file, bits 4–6 indicate the presence of a SQL table, bit 7 indicates the presence of any memo file (either dBASE m PLUS or dBASE for DOS)
		1–3 	              | 3 bytes 	  | Date of last update; formatted as YYMMDD (with YY being the number of years since 1900)
		4–7 	              | 32-bit number |	Number of records in the database file
		8–9 	              | 16-bit number |	Number of bytes in the header
		10–11 	              | 16-bit number | Number of bytes in the record
		12–13 	              | 2 bytes 	  | Reserved; fill with 0
		14 	                  | 1 byte 	      | Flag indicating incomplete transaction[note 1]
		15  	              | 1 byte 	      | Encryption flag[note 2]
		16–27 	              | 12 bytes 	  | Reserved for dBASE for DOS in a multi-user environment
		28              	  | 1 byte 	      | Production .mdx file flag; 1 if there is a production .mdx file, 0 if not
		29                    | 1 byte 	      | Language driver ID
		30–31                 |	2 bytes 	  | Reserved; fill with 0
		32–n [note 3][note 4] |	32 bytes each |	array of field descriptors (see below for layout of descriptors)
		n + 1 	              | 1 byte 	      | 0x0D as the field descriptor array terminator 
	*/

	char a = '\0';
	char b = '\0';
	char c = '\0';

	_file.read(&a, 1);
	version = static_cast<uint8_t>(a);

	char y = '\0';
	char m = '\0';
	char d = '\0';

	_file.read(&y, 1);
	_file.read(&m, 1);
	_file.read(&d, 1);

	date = {
		(static_cast<int>(y) + 1900), 
		static_cast<int>(m), 
		static_cast<int>(d)
	};

	_file.read(&a, 1);
	_file.read(&b, 1);
	_file.read(&c, 1);

	record_count = 
		static_cast<unsigned char>(a)      | 
		static_cast<unsigned char>(b) << 8 | 
		static_cast<unsigned char>(c) << 16;

	_file.read(&a, 1);
	_file.read(&b, 1);

	header_byte_count = static_cast<unsigned char>(a) << 8 | static_cast<unsigned char>(b); 

	_file.read(&a, 1);
	_file.read(&b, 1);

	record_byte_count = static_cast<unsigned char>(a) << 8 | static_cast<unsigned char>(b); 

	_file.seekg(20, std::ios::cur);

	while (static_cast<int>(_file.peek()) != 0x0d) {
		field_descriptors.push_back(Shapefile::Dbf::Header::FieldDescriptor());
		field_descriptors[-1].Parse(_file);
	}

	std::cout << std::endl;

	#ifdef DEBUG_TEXT
	Utils::UI::Note("Version:           " + std::to_string(version));
	Utils::UI::Note("Date (m/d/y):      " + 
		std::to_string(date.m) + "/" + 
		std::to_string(date.d) + "/" + 
		std::to_string(date.y));
	Utils::UI::Note("Record Count:      " + std::to_string(record_count));
	Utils::UI::Note("Header Byte Count: " + std::to_string(header_byte_count));
	Utils::UI::Note("Record Byte Count: " + std::to_string(record_byte_count));
	#endif
}