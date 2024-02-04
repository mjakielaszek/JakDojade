#pragma once
#include"base.h"
class Crossroad : public Base {
private:
	int x;
	int y;
	Base** roads;
	int distance;
public:
	Crossroad();
	Crossroad(int x, int y, int distance, Base** roads) {
		this->x = x;
		this->y = y;
		this->distance = distance;
		this->roads = roads;
	};
};