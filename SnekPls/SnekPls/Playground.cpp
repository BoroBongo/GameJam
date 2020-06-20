#include "Playground.h"


Playground::Playground(int area_widthN, int area_heightN)
{
	area_width = area_widthN;
	area_height = area_heightN;

	vector<vector<wstring> > area_line1(area_height, vector<wstring>(area_width));
	area_line = area_line1;

    for (int i = 0; i < area_height; i++) {
        for (int j = 0; j < area_width; j++) {
            area_line[i][j] = j +(area_width*i);
        }
    }


}

Playground::~Playground()
{

}

int * Playground::getWidth()
{
	return& area_width;
}

int * Playground::getHeight()
{
	return& area_height;
}

std::vector<vector<wstring> > *  Playground::getArray()
{
	return& area_line;
}
