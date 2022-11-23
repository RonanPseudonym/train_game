#include  "../index.hpp"

#include <iostream>

template <typename T>
void Utils::Bitwise::PrintBinary(T number) { // Stolen from the internet. Not made to look pretty, made for debugging
    std::cout << std::bitset<64>(number) << "\n";
}

int Utils::Bitwise::IfstreamToLittleEndianInt(std::ifstream& _file) {
	char a = '\0';
	char b = '\0';
	char c = '\0';
	char d = '\0';

	_file.read(&a, 1);
	_file.read(&b, 1);
	_file.read(&c, 1);
	_file.read(&d, 1);

	return static_cast<unsigned char>(a) | 
		   static_cast<unsigned char>(b) << 8 | 
		   static_cast<unsigned char>(c) << 16 | 
		   static_cast<unsigned char>(d) << 24;
}

int Utils::Bitwise::IfstreamToBigEndianInt(std::ifstream& _file) {
	char a = '\0';
	char b = '\0';
	char c = '\0';
	char d = '\0';

	_file.read(&a, 1);
	_file.read(&b, 1);
	_file.read(&c, 1);
	_file.read(&d, 1);

	return static_cast<unsigned char>(a) << 24| 
		   static_cast<unsigned char>(b) << 16| 
		   static_cast<unsigned char>(c) << 8 | 
		   static_cast<unsigned char>(d);
}

double Utils::Bitwise::IfstreamToLittleEndianDouble(std::ifstream& _file) {
	uint64_t a = Utils::Bitwise::IfstreamToLittleEndianInt(_file);
	uint64_t b = Utils::Bitwise::IfstreamToLittleEndianInt(_file);
	uint64_t c = a | b << 32;

	double d;
	memcpy(&d, &c, sizeof(double));

	return d;
}