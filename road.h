#include "base.h"

class Road :public Base {
private:
	int startX;
	int endX;
	int startY;
	int endY;
	bool hasCity;
	int length;
	int roadIndex;
	Base** cities;
public:
	int getStartX() { return this->startX; };
	int getStartY() { return this->startY; };
	int getEndY() { return this->endY; };
	int getEndX() { return this->endX; };
	bool checkHasCity() { return this->hasCity; };
	int getLength() { return this->length; };
	Road(int startX, int endX, int startY, int endY, int length, bool hasCity, int index) {
		this->endX = endX;
		this->endY = endY;
		this->startX = startX;
		this->startY = startY;
		this->hasCity = hasCity;
		this->length = length;
		this->roadIndex = index;
		this->cities = new Base * [length];
		for (int i = 0; i < length; i++)	cities[i] = nullptr;
	}
	void setCity(bool value) { this->hasCity = value; };
	void setCityReference(Base** city) {
		int i = 0;
		while (i < this->length && this->cities[i] != nullptr) 	i++;
		this->cities[i] = *city;
	};
	Base** getCityOnRoad() { return this->cities; };
	int getRoadIndex() { return this->roadIndex; };
};