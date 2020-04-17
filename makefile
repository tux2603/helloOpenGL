all: bouncingRectangle dancingColors

bouncingRectangle: bouncingRectangle.cpp
	g++ -o bouncingRectangle bouncingRectangle.cpp -lglut -lGL -Wall -Wextra -Wpedantic -ggdb

dancingColors: dancingColors.cpp
	g++ -o dancingColors dancingColors.cpp -lglut -lGL -lGLEW -Wall -Wextra -Wpedantic -ggdb