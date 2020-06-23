#include "Playground.h"


Playground::Playground(int area_widthN, int area_heightN)
{
	previousPos = {0,0};
	srand(time(NULL));
	area_width = area_widthN;
	area_height = area_heightN;
	head_pos = {10,10};
	score = 1;

	vector<vector<wstring> > area_line1(area_height, vector<wstring>(area_width));
	area_line = area_line1;

    for (int i = 0; i < area_height; i++) {
        for (int j = 0; j < area_width; j++) {
            area_line[i][j] = L"_";
        }
    }
	area_line[10][10] = L"X";
	area_line[10][9] = L"0";
	area_line[10][8] = L"1";
	area_line[10][7] = L"2";
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
					return;
				}
				for (int s = 0; s <= score; s++) {
					wstring check = to_wstring(s);
					if (area_line[i][j+1] == check) {
						this->Dead();
						return;
					}
				}
				area_line[i][j] = L"_";
				area_line[i][j+1] = L"X";
				return;
			}
		}
	}

}

void Playground::moveBody() {
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"0") {
				if (i == head_pos[0] && head_pos[1] == j+1) {
					area_line[i][j + 1] = L"0";
					previousPos = {i,j};
					area_line[i][j] = L"_";
					break;
				}
				if (i == head_pos[0] && head_pos[1] == j - 1) {
					area_line[i][j - 1] = L"0";
					previousPos = { i,j };
					area_line[i][j] = L"_";
					break;
				}
				if (i+1 == head_pos[0] && head_pos[1] == j) {
					area_line[i+1][j] = L"0";
					previousPos = { i,j };
					area_line[i][j] = L"_";
					break;
				}
				if (i-1 == head_pos[0] && head_pos[1] == j) {
					area_line[i-1][j] = L"0";
					previousPos = { i,j };
					area_line[i][j] = L"_";
					break;
				}
			}
		}
	}

	wstring check;
	for (int k = 1; k <= score; k++) {
		bool found = false;
		check = to_wstring(k);
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
				if (area_line[i][j] == check) {
					found = true;
					if (j + 2 <= (area_width - 1)) {
						if (area_line[i][j + 2] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[previousPos[0]][previousPos[1]] = L"_";
							continue;
						}
					}
					if (j - 2 >= 0) {
						if (area_line[i][j - 2] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i + 2 <= (area_height - 1)) {
						if (area_line[i + 2][j] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i - 2 >= 0) {
						if (area_line[i - 2][j] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i + 1 <= (area_height - 1) && j + 1 <= (area_width - 1)) {
						if (area_line[i + 1][j + 1] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i - 1 >= 0 && j - 1 >= 0) {
						if (area_line[i - 1][j - 1] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i - 1 >= 0 && j + 1 <= (area_width - 1)) {
						if (area_line[i - 1][j + 1] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
					if (i + 1 <= (area_height - 1) && j - 1 >= 0) {
						if (area_line[i + 1][j - 1] == to_wstring(k - 1)) {
							area_line[previousPos[0]][previousPos[1]] = check;
							previousPos = { i,j };
							area_line[i][j] = L"_";
							continue;
						}
					}
				}
				if (i == area_height-1 && j == area_width-1) {
					if (!found) {
						area_line[previousPos[0]][previousPos[1]] = check;
						previousPos = { i,j };
					}
				}
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
				for (int s = 0; s <= score; s++) {
					wstring check = to_wstring(s);
					if (area_line[i][j - 1] == check) {
						this->Dead();
						return;
					}
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
				for (int s = 0; s <= score; s++) {
					wstring check = to_wstring(s);
					if (area_line[i-1][j] == check) {
						this->Dead();
						return;
					}
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
				for (int s = 0; s <= score; s++) {
					wstring check = to_wstring(s);
					if (area_line[i+1][j] == check) {
						this->Dead();
						return;
					}
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
	this->setHeadPos();
	if (dead) {
		return;
	}
	switch (movedir) {
	case Moving::UP: {
		this->moveUp();
		this->moveBody();
		break;
	}
	case Moving::DOWN: {
		this->moveDown();
		this->moveBody();
		break;
	}
	case Moving::LEFT: {
		this->moveLeft();
		this->moveBody();
		break;
	}
	case Moving::RIGHT: {
		this->moveRight();
		this->moveBody();
		break;
	}
	}
}

void Playground::setHeadPos() {
	for (int i = 0; i < area_height; i++) {
		for (int j = 0; j < area_width; j++) {
			if (area_line[i][j] == L"X") {
				head_pos = {i,j};
				return;
			}
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
		int x = rand() % (area_height - 3) + 1;
		int y = rand() % (area_width - 3) + 1;
		for (int s = 0; s <= score; s++) {
			wstring check = to_wstring(s);
			if (area_line[x][y] == check ||( x == previousPos[0] && y == previousPos[1])) {
				continue;
			}
				if (x != head_pos[0] && y != head_pos[1]) {
					area_line[x][y] = L"B";
					berry_pos = { x,y };
					return;
				}
		}
	}
}

void Playground::Dead() {
	dead = true;
}
