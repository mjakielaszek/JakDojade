#pragma once
#include <iostream>
#include "list.h"
#include "city.h"
#include "road.h"
#include "crossroad.h"
#define CROSSES 4
#define BUFF 50
class MapInfo {
	int xSize;
	int ySize;
	int cityCount;
	int roadCount;
	char** map;
	int** matrix;
	DoubleList* cityList;
	DoubleList* roadList;
	DoubleList** connectionsList;
public:
	MapInfo() {};
	MapInfo(int x, int y) {
		this->roadCount = 0;
		this->cityCount = 0;
		this->xSize = x;
		this->ySize = y;
		this->map = (char**)malloc(getX() * sizeof(char*));
		for (int i = 0; i < getX(); i++)	map[i] = (char*)malloc(getY() * sizeof(char));
	};
	Base** findRoadsOnCoordinates(int x, int y, int oldRoadIndex);
	Base** findCityOnRoad(Base* base);
	void setConnections(DoubleList** connections) { this->connectionsList = connections; };
	int getX() { return this->xSize; };
	int getY() { return this->ySize; };
	void setCityList(DoubleList** head) {
		this->cityList = *head;
	};
	void setHorizontalList(DoubleList** head) {
		this->roadList = *head;
	};
	void setVerticalList(DoubleList** head) {
		this->roadList = *head;
	};
	void setSlice(char buff[], int y) {
		for (int i = 0; i < getX(); i++)	
			this->map[i][y] = buff[i];
	};
	void getPositions();
	void getVerticalRoad(int* x, int* y);
	void getHorizontalRoad(int *x, int *y) ;
	void getCityPosition(int x, int y);
	void newCity(int x, int y, int xPos, int yPos);
	void getNeighbours();
	void findNextRoad(int x, int y, int currentLength, int startCity, int oldRoadIndex);
	void addCity() { this->cityCount++; };
	void addRoad() { this->roadCount++; };
	int getRoadCount() { return this->roadCount; };
	int getCityCount() { return this->cityCount; };
	void makeArr();
	int getConnectionLength(int cityIndex1, int cityIndex2);
private :
	bool IsTheSamePoint(int x, int y, int x1, int y1) {
		return (x == x1) && (y == y1);
	}
	bool checkForDuplicates(int newStart, int newEnd, int newLength);
};

