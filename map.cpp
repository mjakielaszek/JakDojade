#include "map.h"
#include "fligths.h"
void MapInfo::getPositions() {
	for (int j = 0; j < getY(); j++) {
		for (int i = 0; i < getX(); i++) {
			if (i < getX() - 1 && (this->map[i][j] == '#' || this->map[i][j] == '*') && (this->map[i + 1][j] == '#' || this->map[i + 1][j] == '*')) {
				getHorizontalRoad(&i, &j);
				i -= 2;
			}
		}
	}
	for (int i = 0; i < getX(); i++) {
		for (int j = 0; j < getY(); j++) {
			if (j < getY() - 1 && (this->map[i][j] == '#' || this->map[i][j] == '*') && (this->map[i][j + 1] == '#' || this->map[i][j + 1] == '*')) {
				getVerticalRoad(&i, &j);
				j -= 2;
			}
		}
	}
	for (int j = 0; j < getY(); j++) {
		for (int i = 0; i < getX(); i++) {
			if (this->map[i][j] == '*')	getCityPosition(i, j);
		}
	}
};

void MapInfo::getVerticalRoad(int* x, int* y) {
	int roadStart = *y;
	bool hasCity = false;
	bool firstLoop = true;
	Base** cities;
	while (*y < getY() && (this->map[*x][*y] == '#' || this->map[*x][*y] == '*')) {
		if (!firstLoop && *x < getX() - 1 && (this->map[*x + 1][*y] == '#' || this->map[*x + 1][*y] == '*')) {
			(*y)++;
			break;
		}
		if (!firstLoop && *x > 0 && (this->map[*x - 1][*y] == '#' || this->map[*x - 1][*y] == '*')) {
			(*y)++;
			break;
		}
		if (this->map[*x][*y] == '*') {
			hasCity = true;
			if (!firstLoop){
				(*y)++;
				break;
			}
		}
		(*y)++;
		firstLoop = false;
	}
	int roadEnd = *y - 1;
	int roadLength = roadEnd - roadStart + 1;
	add_in_back(&roadList, new Road(*x, *x, roadStart, roadEnd, roadLength, hasCity, getRoadCount()));
	addRoad();
};

void MapInfo::getHorizontalRoad(int* x, int* y) {
	int roadStart = *x;
	bool hasCity = false;
	bool firstLoop = true;
	while (*x < getX() && (this->map[*x][*y] == '#' || this->map[*x][*y] == '*')) {
		if (!firstLoop && *y < getY() - 1 && (this->map[*x][*y + 1] == '#' || this->map[*x][*y + 1] == '*')) {
			(*x)++;
			break;
		}
		if (!firstLoop && *y > 0 && (this->map[*x][*y - 1] == '#' || this->map[*x][*y - 1] == '*')) {
			(*x)++;
			break;
		}
		if (this->map[*x][*y] == '*') {
			hasCity = true;
			if (!firstLoop) {
				(*x)++;
				break;
			}
		}
		(*x)++;
		firstLoop = false;
	}
	int roadEnd = *x - 1;
	int roadLength = roadEnd - roadStart + 1;
	add_in_back(&roadList, new Road(roadStart, roadEnd, *y, *y, roadLength, hasCity, getRoadCount()));
	addRoad();
};

void MapInfo::getCityPosition(int x, int y) {
	if (x > 0 && y > 0 && this->map[x - 1][y - 1] > 64 && this->map[x - 1][y - 1] < 123) newCity(x - 1, y - 1, x, y);

	else if (y < getY() - 1 && x < getX() - 1 && this->map[x + 1][y + 1] > 64 && this->map[x + 1][y + 1] < 123)	newCity(x + 1, y + 1, x, y);

	else if (x > 0 && y < getY() - 1 && this->map[x - 1][y + 1] > 64 && this->map[x - 1][y + 1] < 123)	newCity(x - 1, y + 1, x, y);

	else if (y > 0 && x < getX() - 1 && this->map[x + 1][y - 1] > 64 && this->map[x + 1][y - 1] < 123)	newCity(x + 1, y - 1, x, y);

	else if (x < getY() - 1 && this->map[x + 1][y] > 64 && this->map[x + 1][y] < 123)	newCity(x + 1, y, x, y);

	else if (x > 0 && this->map[x - 1][y] > 64 && this->map[x - 1][y] < 123)	newCity(x - 1, y, x, y);

	else if (y < getY() - 1 && this->map[x][y + 1] > 64 && this->map[x][y + 1] < 123)	newCity(x, y + 1, x, y);

	else if (y > 0 && this->map[x][y - 1] > 64 && this->map[x][y - 1] < 123)	newCity(x, y - 1, x, y);
};

void MapInfo::newCity(int x, int y, int xPos, int yPos) {
	while (this->map[x][y] > 64 && this->map[x][y] < 123)	x--;
	int i = 1;
	int cityCounter = 0;
	char* cityName = new char[BUFF];
	while (this->map[x + i][y] > 64 && this->map[x + i][y] < 123) {
		cityName[cityCounter] = this->map[x + i][y];
		i++;
		cityCounter++;
	}
	Base** roads = findRoadsOnCoordinates(xPos, yPos, 2*getRoadCount());
	Base* city = new City(xPos, yPos, cityName, roads, getCityCount());
	addCity();
	add_in_back(&cityList, city);
	int k = 0;
	while (roads[k] != nullptr) {
		Road* road = (Road*)roads[k];
		road->setCityReference(&city);
		k++;
	}
};

Base** MapInfo::findRoadsOnCoordinates(int x, int y, int oldRoadIndex) {
	DoubleList* current = roadList;
	Road* road;
	Base** roads = new Base * [CROSSES];
	for (int i = 0; i < CROSSES; i++) roads[i] = nullptr;
	int slot = 0;
	bool theSame;
	while (current != NULL && slot < CROSSES) {
		theSame = false;
		road = (Road*)current->base;
		if (road->getRoadIndex() == oldRoadIndex) theSame = true;
		if (!theSame && (road->getStartX() <= x && road->getEndX() >= x) && (road->getStartY() <= y && road->getEndY() >= y)) {
			roads[slot] = road;
			slot++;
		}
		current = current->next;
		if (current->next == NULL) {
			break;
		}
	}
	if (slot == 0) return nullptr;
	else return roads;
}

Base** MapInfo::findCityOnRoad(Base* base) {
	Road* road = (Road*)base;
	Base** cities = road->getCityOnRoad();
	return cities;
}

// otherX otherY - coordinates of the beginning of the current road to not duplicate it when searching for roads
// x y - coordinates of the end of the current road
void MapInfo::findNextRoad(int x, int y, int currentLength, int startCity, int oldRoadIndex) {
	Base** roads = findRoadsOnCoordinates(x, y, oldRoadIndex);
	int ammRoads = 0;
	int fromCrossToCity = 0;
	while (roads[ammRoads] != nullptr) ammRoads++;
	for (int i = 0; i < ammRoads; i++) {
		Road* road = (Road*)roads[i];
		if (road->checkHasCity()) {
			City** cities = (City**)road->getCityOnRoad();
			int cityCount = 0;
			while (cities[cityCount] != nullptr) cityCount++;
			for (int i = 0; i < cityCount; i++) {
				fromCrossToCity = 0;
				if (cities[i]->getX() == x) {
					fromCrossToCity = abs(cities[i]->getY() - y);
					if (checkForDuplicates(startCity, cities[i]->getCityIndex(), currentLength+fromCrossToCity))
						add_in_back(connectionsList, new Connection(startCity, cities[i]->getCityIndex(), currentLength + fromCrossToCity));
				}
				else if (cities[i]->getY() == y) {
					fromCrossToCity = abs(cities[i]->getX() - x);
					if (checkForDuplicates(startCity, cities[i]->getCityIndex(), currentLength + fromCrossToCity))
						add_in_back(connectionsList, new Connection(startCity, cities[i]->getCityIndex(), currentLength + fromCrossToCity));
				}
			}
		}
		else {
			if (IsTheSamePoint(x, y, road->getStartX(), road->getStartY())) {
				findNextRoad(road->getEndX(), road->getEndY(), currentLength + road->getLength() - 1, startCity, road->getRoadIndex());
			}
			else {
				findNextRoad(road->getStartX(), road->getStartY(), currentLength + road->getLength() - 1, startCity, road->getRoadIndex());
			}
		}
	}
}

void MapInfo::getNeighbours() {
	DoubleList* current = cityList;
	while (current->next != NULL) {
		City* city = (City*)current->base;
		int distance = 0;
		int startName = city->getCityIndex();
		int roadCount = city->countRoads();
		int i = 0;
		Base** roads = new Base * [CROSSES];
		while (city->getRoad(i) != nullptr) {
			roads[i] = city->getRoad(i);
			i++;
		}
		for (int i = 0; i < roadCount; i++) {		
			distance = 0;
			Road* road = (Road*)roads[i];
			distance = road->getLength();			
			if (this->IsTheSamePoint(city->getX(), city->getY(), road->getStartX(), road->getStartY())) {
				findNextRoad(road->getEndX(), road->getEndY(), distance, startName, road->getRoadIndex());
			}
			else {
				findNextRoad(road->getStartX(), road->getStartY(), distance, startName, road->getRoadIndex());
			}
		}
		current = current->next;
	}
}

bool MapInfo::checkForDuplicates(int newStart, int newEnd, int newLength) {
	DoubleList* current = *connectionsList;
	while (current->next != NULL) {
		Connection* route = (Connection*)current->base;
		if (route->getStartIndex() == newEnd && route->getEndIndex() == newStart) {
			if (newLength <= route->getLength()) {
				route->changeLength(newLength);
				return false;
			}
		}
		current = current->next;
	}
	return true;
}

void MapInfo::makeArr() {
	int ammOfCities = getCityCount();
	this->matrix = (int**)malloc(ammOfCities * sizeof(int*));
	for (int i = 0; i < ammOfCities; i++)	matrix[i] = (int*)malloc(ammOfCities * sizeof(int));
	for (int j = 0; j < ammOfCities; j++) {
		for (int i = j; i < ammOfCities; i++) {
			int distance = getConnectionLength(i, j);
			matrix[i][j] = distance;
			matrix[j][i] = distance;
		}
	}
}

int MapInfo::getConnectionLength(int cityIndex1, int cityIndex2) {
	DoubleList* current = *connectionsList;
	while (current->next != nullptr) {
		Connection* connection = (Connection*)current->base;
		int startIndex = connection->getStartIndex();
		int endIndex = connection->getEndIndex();
		int distance = 0;
		if ((startIndex == cityIndex1 && endIndex == cityIndex2) || (startIndex == cityIndex2 && endIndex == cityIndex1)) {
			distance = connection->getLength();
			return distance;
		}
		current = current->next;
	}
	return 0;
}