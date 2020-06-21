#pragma once
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <memory>
#include <crtdbg.h>

using namespace std;

class Playground
{
	int area_width;
	int area_height;
	vector<vector<wstring> > area_line;



public:
	int score =-1;
	bool dead = false;
	enum class Moving
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	Moving movedir = Moving::RIGHT;

	Playground(int area_widthN, int area_heightN);
	~Playground();
	int * getWidth();
	int * getHeight();
	vector<vector<wstring> > * getArray();

	void moveRight(float elapsed_f);

	void moveLeft(float elapsed_f);

	void moveUp(float elapsed_f);

	void moveDown(float elapsed_f);

	void move(float elapsed_f);

	void ClickRight();
	void ClickLeft();
	void ClickUp();
	void ClickDown();

	void Dead();
	void ResetBerry();
};

