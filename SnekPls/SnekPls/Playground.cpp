#include "Playground.h"


Playground::Playground(int area_widthN, int area_heightN)
{
	area_width = area_widthN;
	area_height = area_heightN;

	vector<vector<char> > area_line(area_height, vector<char>(area_width));

    for (int i = 0; i < area_height; i++) {
        for (int j = 0; j < area_width; j++) {
            area_line[i][j] = j + i + 1;
        }
    }


}

Playground::~Playground()
{

}

int * Playground::getWidth()
{
	return &area_width;
}

int * Playground::getHeight()
{
	return &area_height;
}

std::vector<char> * Playground::getArray()
{
	return &area_line;
}
