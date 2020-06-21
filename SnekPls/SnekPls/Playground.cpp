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
	this->ResetBerry();

	//to_wstring(j +(area_width*i))

	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (i==0) {
				area_line[i][j] = L"W";
			}
			if (j==0) {
				area_line[i][j] = L"W";
			}
			if (j == area_width - 1) {
				area_line[i][j] = L"W";
			}
			if (i == area_height-1) {
				area_line[i][j] = L"W";
			}
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

std::vector<vector<wstring> > * Playground::getArray()
{
	return& area_line;
}

void Playground::moveRight()
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j]==L"X" && (j+1)!=area_width) {
				if (area_line[i][j+1] == L"B") {
					this->ResetBerry();
				}
				if (area_line[i ][j+1] == L"W") {
					this->Dead();
				}
				area_line[i][j] = L"_";
				area_line[i][j+1] = L"X";
				return;
			}
		}
	}

}

void Playground::moveLeft()
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (j - 1) != -1) {
				if (area_line[i][j - 1] == L"B") {
					this->ResetBerry();
				}
				if (area_line[i ][j-1] == L"W") {
					this->Dead();
				}
				area_line[i][j] = L"_";
				area_line[i][j - 1] = L"X";
				return;
			}
		}
	}
}

void Playground::moveUp()
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (i - 1) != -1) {
				if (area_line[i-1][j] == L"B") {
					this->ResetBerry();
				}
				if (area_line[i - 1][j] == L"W") {
					this->Dead();
				}
				area_line[i][j] = L"_";
				area_line[i-1][j] = L"X";
				return;
			}
		}
	}
}

void Playground::moveDown()
{
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X" && (i + 1) != area_width) {
				if (area_line[i+1][j] == L"B") {
					this->ResetBerry();
				}
				if (area_line[i + 1][j] == L"W") {
					this->Dead();
				}
				area_line[i][j] = L"_";
				area_line[i+1][j] = L"X";
				return;
			}
		}
	}

}

void Playground::move(std::chrono::milliseconds elapsed_f)
{
	if (dead) {
		return;
	}
	switch (movedir) {
	case Moving::UP: {
		this->moveUp();
		break;
	}
	case Moving::DOWN: {
		this->moveDown();
		break;
	}
	case Moving::LEFT: {
		this->moveLeft();
		break;
	}
	case Moving::RIGHT: {
		this->moveRight();
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
	this->score += 1;
	while (1) {
		int x = rand() % (area_height - 2) + 1;
		int y = (rand() % (area_width - 2)) + 1;
		if (x != 10 && y != 10) {
			area_line[x][y] = L"B";
			return;
		}
	}
}

void Playground::Dead() {
	dead = true;
}
