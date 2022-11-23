#include <string>
#include <fstream>
#include <vector> // I don't like how inexplicit & memory-inefficient using vectors here is, but the length of these arrays isn't know at compile time, but only at the beginning of runtime

#include <stdint.h>

#include "../utils/index.hpp"

// ESRI Shapefile Technichal Specifications: https://www.esri.com/content/dam/esrisites/sitecore-archive/Files/Pdfs/library/whitepapers/pdfs/shapefile.pdf

namespace Shapefile {
	namespace General {
		typedef struct {
			double x_min;
			double x_max;
			double y_min;
			double y_max;
		} BoundingBox;

		typedef struct {
			double x;
			double y;
		} Point;

		enum ShapeType {
			POINT = 1,
			POLYGON = 5,
		};

		class Header {
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

			public:
				uint32_t	file_length;  // 24-28
				uint32_t	version;      // 28-32
				ShapeType   shape_type;   // 32-36
				BoundingBox bounding_box; // 36-68

					 Header();
				void Parse(std::ifstream& _file);
		};
	}
	namespace Shp {
		namespace Shape {
			class BaseShape {
				public:
					             BaseShape();
					virtual     ~BaseShape();
					virtual void Parse(std::ifstream& _file);

					uint32_t record_number;
					uint32_t content_length;
			};

			class Point : public BaseShape {
				/*
					Position |    Field   | Value |  Type   | Number | Order

					Byte 0   | Shape Type | 1     | Integer | 1      | Little
					Byte 4   | X          | X     | Double  | 1      | Little
					Byte 12  | Y          | Y     | Double  | 1      | Little
				*/

				public:
					double x;
					double y;

					void Parse(std::ifstream& _file);
			};

			class Polygon : public BaseShape {
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

				public:
                    Shapefile::General::BoundingBox        bounding_box;
					uint32_t                               num_parts;
					uint32_t                       	       num_points;
					std::vector<uint32_t>                  parts;
					std::vector<Shapefile::General::Point> points;

					void Parse(std::ifstream& _file);
			};
		}

		class Index {
			public:
                Shapefile::General::Header header;
				std::vector<Shape::BaseShape*> records;

                     Index();
                void Parse(std::ifstream& _file);
		};
	}

	namespace Shx {
		class IndexRecord {
			/*
				Position |     Field      |      Value     |  Type   | Order

				Byte 0   | Offset         | Offset         | Integer | Big
				Byte 4   | Content Length | Content Length | Integer | Big
			*/

			public:
				uint32_t offset;
				uint32_t content_length;

					 IndexRecord();
				void Parse(std::ifstream& _file);
		};

		class Index {
			public:
				Shapefile::General::Header header;
				std::vector<IndexRecord> records;

				     Index();
				void Parse(std::ifstream& _file);
		};
	}

	namespace Dbf {
		namespace Header {
			class FieldDescriptor {
				/*
					 Byte | Contents |             Meaning

					0–10  | 11 bytes | Field name in ASCII (zero-filled)
					11 	  | 1 byte 	 | Field type. Allowed values: C, D, F, L, M, or N (see next table for meanings)
					12–15 | 4 bytes  | Reserved
					16    | 1 byte   | Field length in binary (maximum 254 (0xFE)).
					17 	  | 1 byte 	 | Field decimal count in binary
					18–19 | 2 bytes  | Work area ID
					20 	  | 1 byte 	 | Example
					21–30 | 10 bytes | Reserved
					31 	  | 1 byte   | Production MDX field flag; 1 if field has an index tag in the production MDX file, 0 if not
				*/

				public:
						std::string field_name; 

					     FieldDescriptor();
					void Parse(std::ifstream& _file);
			};

			class Index {
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

				public:
					uint8_t                      version;
					struct {
						int y;
						int m;
						int d;
					}                            date;
					uint32_t                     record_count;
					uint16_t                     header_byte_count;
					uint16_t                     record_byte_count;
					std::vector<FieldDescriptor> field_descriptors;

						 Index();
					void Parse(std::ifstream& _file);
			};
		}

		class Index {
			public:
				Header::Index header;

					 Index();
				void Parse(std::ifstream& _file);
		};
	}

	class Parser {
		public:
			std::string path;

			     Parser(std::string _path);
			void Load  ();
			void Parse ();

            Shapefile::Shp::Index shp;
            Shapefile::Shx::Index shx;
            Shapefile::Dbf::Index dbf;

		private:
			std::ifstream shp_f;
			std::ifstream shx_f;
			std::ifstream dbf_f;
	};
}