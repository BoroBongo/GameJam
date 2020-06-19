#pragma once
#include <vector>

using namespace std;

class Playground
{
	int area_width;
	int area_height;

	vector<char>  area_line;

public:
	Playground(int area_widthN, int area_heightN);
	~Playground();
	int * getWidth();
	int * getHeight();
	vector<char> * getArray();
};

