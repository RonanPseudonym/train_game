FLAGS := -Wall -pedantic -std=c++11
CC    := g++
C     := src/main.cpp src/shapefile/parser.cpp src/shapefile/shp/shape/point.cpp src/utils/bitwise/index.cpp src/shapefile/general/header.cpp src/utils/ui/index.cpp src/utils/ui/color/index.cpp src/shapefile/shp/index.cpp src/shapefile/shp/shape/polygon.cpp src/shapefile/shp/shape/base_shape.cpp src/shapefile/shx/index.cpp src/shapefile/shx/index_record.cpp

NAME  := rails # Working title obviously

build: $(C)
	$(CC) $(C) -o $(NAME) $(FLAGS)

run: build
	./$(NAME)

install: build
	cp $(NAME) /usr/local/bin/
	chmod +x /usr/local/bin/$(NAME)
