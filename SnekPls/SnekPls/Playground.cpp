#include "Playground.h"


Playground::Playground(int area_widthN, int area_heightN)
{
	srand(time(NULL));
	area_width = area_widthN;
	area_height = area_heightN;

	vector<vector<wstring> > area_line1(area_height, vector<wstring>(area_width));
	area_line = area_line1;

    for (int i = 0; i < area_height; i++) {
        for (int j = 0; j < area_width; j++) {
            area_line[i][j] = L"_";
        }
    }
	area_line[10][10] = L"X";
	area_line[rand() % area_heightN][rand() % area_widthN] = L"B";

	//to_wstring(j +(area_width*i))

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

void Playground::moveRight(float elapsed_f)
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j]==L"X" && (j+1)!=area_width) {
				if (area_line[i][j+1] == L"B") {
					this->ResetBerry();
				}
				area_line[i][j] = L"_";
				area_line[i][j+1] = L"X";
				return;
			}
		}
	}

}

void Playground::moveLeft(float elapsed_f)
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (j - 1) != -1) {
				if (area_line[i][j - 1] == L"B") {
					this->ResetBerry();
				}
				area_line[i][j] = L"_";
				area_line[i][j - 1] = L"X";
				return;
			}
		}
	}
}

void Playground::moveUp(float elapsed_f)
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (i - 1) != -1) {
				if (area_line[i-1][j] == L"B") {
					this->ResetBerry();
				}
				area_line[i][j] = L"_";
				area_line[i-1][j] = L"X";
				return;
			}
		}
	}
}

void Playground::moveDown(float elapsed_f)
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (i + 1) != area_width) {
				if (area_line[i+1][j] == L"B") {
					this->ResetBerry();
				}
				area_line[i][j] = L"_";
				area_line[i+1][j] = L"X";
				return;
			}
		}
	}

}

void Playground::move(float elapsed_f)
{
	switch (movedir) {
	case Moving::UP: {
		this->moveUp(elapsed_f);
		break;
	}
	case Moving::DOWN: {
		this->moveDown(elapsed_f);
		break;
	}
	case Moving::LEFT: {
		this->moveLeft(elapsed_f);
		break;
	}
	case Moving::RIGHT: {
		this->moveRight(elapsed_f);
		break;
	}
	}
}

void Playground::ClickRight()
{
	if (movedir != Moving::LEFT) {
		movedir = Moving::RIGHT;
	}
}

void Playground::ClickLeft()
{
	if (movedir != Moving::RIGHT) {
		movedir = Moving::LEFT;
	}
}

void Playground::ClickUp()
{
	if (movedir != Moving::DOWN) {
		movedir = Moving::UP;
	}
}

void Playground::ClickDown()
{
	if (movedir != Moving::UP) {
		movedir = Moving::DOWN;
	}
}

void Playground::ResetBerry()
{
	area_line[rand() % area_height][rand() % area_width] = L"B";
}
