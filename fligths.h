#pragma once
#include "base.h"
#include "list.h"
#include "city.h"

class Connection : public Base {
	int start;
	int end;
	int time;
	DoubleList* connectionsList;
	DoubleList** cityList;
public:
	int findCityIndexByName(char buff[]);
	void setCityList(DoubleList** list) { this->cityList = list; };
	void setConnections(DoubleList** head) { this->connectionsList = *head; };
	Connection() {};
	Connection(int start, int end, int time) {
		this->start = start;
		this->end = end;
		this->time = time;
	};
	void findCities(char buff[]);
	int findName(char buff[], int* i);
	char* setName(char buff[], int start, int end, bool destination);
	DoubleList* getConnectionsList() { return this->connectionsList; };
	int getStartIndex() { return this->start; };
	int getEndIndex() { return this->end; };
	int getLength() { return this->time; };
	void changeLength(int distance) { this->time = distance; };
	char* findCityNameByIndex(int index);
};