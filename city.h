#pragma once
#include "base.h"
class City :public Base {
	int x;
	int y;
	char* name;
	Base** roads;
	int cityIndex;
public:
	City();
	City(int x, int y, char name[], Base** roads, int cityIndex) {
		this->x = x;
		this->y = y;
		this->name = name;
		this->roads = roads;
		this->cityIndex = cityIndex;
	}
	int getCityIndex() { return this->cityIndex; };
	int getX() { return this->x; };
	int getY() { return this->y; };
	Base* getRoad(int x) { return this->roads[x]; };
	int countRoads() {
		int k = 0;
		for (int i = 0; i < CROSSES; i++) {
			if (this->roads[i] != nullptr) k++;
		}
		return k;
	};
	Base** getAllRoads() { return this->roads; };
	char* getName() { return this->name; };
};