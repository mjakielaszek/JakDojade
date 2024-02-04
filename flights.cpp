#include <iostream>

#include "fligths.h"

void Connection::findCities(char buff[]) {
	int i = 0;
	int firstStart = findName(buff, &i);
	char* beggining = setName(buff, firstStart, i, false);
	int secondStart = findName(buff, &i);
	char* destination = setName(buff, secondStart, i, true);
	while (buff[i] < 48 || buff[i] >57) i++;
	int timeStart = i;
	while (buff[i] > 47 && buff[i] < 58) i++;
	int timeLength = i - timeStart;
	char* time = new char[timeLength];
	for (int j = 0; j < timeLength; j++)	time[j] = buff[timeStart + j];
	int timeInt = atoi(time);
	add_in_back(&connectionsList, new Connection(findCityIndexByName(beggining), findCityIndexByName(destination), timeInt));
};

int Connection::findName(char buff[], int* i) {
	while (buff[*i] < 65 || buff[*i] >122) (*i)++;
	int start = *i;
	while (buff[*i] > 64 && buff[*i] < 123) (*i)++;
	return start;
};

char* Connection::setName(char buff[], int start, int end, bool destination) {
	if (!destination) {
		char* first = new char[end - start];
		for (int i = 0; i < end - start; i++) {
			first[i] = buff[start + i];
		}
		return first;
	}
	if (destination) {
		char* second = new char[end - start];
		for (int i = 0; i < end - start; i++) {
			second[i] = buff[start + i];
		}
		return second;
	}
};

int Connection::findCityIndexByName(char buff[]) {
	DoubleList* current = *cityList;
	bool next = false;
	while (current->next != nullptr) {
		next = false;
		City* city = (City*)current->base;
		char* cityName = city->getName();
		int searchedLength = 0;
		while (buff[searchedLength] > 64 && buff[searchedLength] < 123)searchedLength++;
		for (int i = 0; i < searchedLength; i++) {
			if (buff[i] != cityName[i]) {
				current = current->next;
				next = true;
				break;
			}
		}
		if (!next) return city->getCityIndex();
	}
}

char* Connection::findCityNameByIndex(int index) {
	DoubleList* current = *cityList;
	while (current->next != nullptr) {
		City* city = (City*)current->base;
		if (city->getCityIndex() == index) return city->getName();
		current = current->next;
	}
}